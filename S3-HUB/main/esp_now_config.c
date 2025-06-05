#include <globalVar.h>


bool mesh_system_active = CLOSED;
walkie_pairing_mode_t walkie_pairing_mode = NONE;
uint8_t device_sta_mac[6];
uint8_t peer_addresses[8][6];
uint8_t temp_peer_addr[6];
uint8_t number_paired_peers = 1; // 1 is us
uint8_t new_peers  = 0;



esp_err_t init_wifi(void){
    wifi_config_t default_cfg = {
        .sta = {
            .ssid = "",
            .password = "",
            .channel = ESP_NOW_CHANNEL
        }
    };

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
    assert(ap_netif);
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(station_reconfig());
    esp_read_mac(device_sta_mac, ESP_MAC_WIFI_STA);
    memcpy(peer_addresses[0], device_sta_mac, ESP_NOW_ETH_ALEN);
    return ESP_OK;
}

esp_err_t station_reconfig(void){

    wifi_config_t default_cfg = {
        .sta = {
            .ssid = "",
            .password = "",
            .channel = ESP_NOW_CHANNEL
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &default_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ESP_OK;
}

esp_err_t master_reconfig(void){

    wifi_config_t master_cfg = {
        .sta = {
            .ssid = "",
            .password = "",
            .channel = ESP_NOW_CHANNEL
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &master_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ESP_OK;
}

esp_err_t slave_reconfig(void){

     wifi_config_t slave_cfg = {
        .ap = {
            .ssid = DEVICE_PAIRING_NAME,
            .password = "",
            .channel = ESP_NOW_CHANNEL,
            .ssid_len = strlen(DEVICE_PAIRING_NAME),
            .authmode = WIFI_AUTH_OPEN,
            .max_connection = DEFAULT_SCAN_LIST_SIZE,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &slave_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ESP_OK;
}

esp_err_t init_esp_now(void){
    
    esp_err_t err = esp_now_init();

    if(err != ESP_OK){
        return ESP_FAIL;
    }

    ESP_ERROR_CHECK(esp_now_register_send_cb(esp_now_sent_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(esp_now_recv_cb));

    return ESP_OK;

}
void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status){
}

void esp_now_recv_cb(const uint8_t *mac_addr,  const uint8_t *data, int data_len){
    switch (walkie_pairing_mode)
    {
        case NONE:
            if(esp_now_is_peer_exist(mac_addr) == true && data_len == 1){
                printf("%d\n", data[0]);
            }
            break;
        
        case MASTER:
            if(esp_now_is_peer_exist(data) == false){
                walkie_pairing_new_mesh(data);
            }
            break;

        case SLAVE:
            
            if(data_len == 6){
                esp_now_peer_info_t peer_info = {0};
                memcpy(peer_info.peer_addr, data, ESP_NOW_ETH_ALEN);
                peer_info.channel = ESP_NOW_CHANNEL;
                peer_info.encrypt = false;

                if (esp_now_add_peer(&peer_info) == ESP_OK) {
                    if (number_paired_peers < mesh_system_max_connection) {
                        // Optional: give time for connection
                        vTaskDelay(pdMS_TO_TICKS(5));
                        esp_now_send( data, device_sta_mac, sizeof(device_sta_mac));
                        esp_now_del_peer(peer_info.peer_addr);
                        walkie_pairing_mode = SYNC;
                        number_paired_peers = 0;
                    } else {
                        // Max connections reached, remove peer
                        walkie_pairing_max(data);
                    }
                }
            }
            // if(data_len == 6){
                
            

            
            //     }

                
            // }
            break;

        case SYNC:
            if(data_len == 6){
                walkie_pairing_sync(data);
            }else{
                
                //host_uart_write_str(WALKIE_PAIRING_COMPLETE);
                walkie_pairing_mode = NONE;
            }
            break;
        default:
            break;
    }
}

void walkie_discover_peers(void){

    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    while (1)
    {
        esp_wifi_scan_start(NULL, true);
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
        
        for (int i = 0; i < ap_count; i++){
            if(strcmp((const char *)ap_info[i].ssid, DEVICE_PAIRING_NAME) == 0){
                bool is_inList = false; // check if mac addr is already in list
                for(int j = 0; j < number_paired_peers; j++){
                    if(memcmp(peer_addresses[j], ap_info[i].bssid, 6) == 0){
                        is_inList = true;
                        break;
                    }
                    
                }

                if(is_inList == false){
                    request_sta_mac_addr(ap_info[i].bssid);
                }

            }
        }
        break;
    }

}

void request_sta_mac_addr(uint8_t *mac_addr){
    
    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, mac_addr, ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.encrypt = false;

    if (esp_now_add_peer(&peer_info) == ESP_OK) {
        // Request STA
        uint8_t msg = WALKIE_REQUEST_STA_MAC;
        esp_now_send(mac_addr, device_sta_mac, sizeof(device_sta_mac));
        vTaskDelay(pdMS_TO_TICKS(50));
        // remove from peer stack
        esp_now_del_peer(mac_addr);

    }

}


esp_err_t remove_peer_from_mesh(uint8_t *mac_addr){

    return esp_now_del_peer(mac_addr);
}

void walkie_pairing_max(uint8_t *addr){
    esp_now_del_peer(addr);
    //send message beep flash some color idk
}

void walkie_pairing_new_mesh(uint8_t *addr){

    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, addr, ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.encrypt = false;

    if (esp_now_add_peer(&peer_info) == ESP_OK) {
        if (number_paired_peers < mesh_system_max_connection) {
            memcpy(peer_addresses[number_paired_peers], addr, ESP_NOW_ETH_ALEN);
            // Optional: give time for connection
            vTaskDelay(pdMS_TO_TICKS(5));
            // Send test byte
            number_paired_peers += 1;
            new_peers += 1;
        }
    }

}
