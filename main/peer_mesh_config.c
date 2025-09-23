#include <globlaVar.h>

uint8_t new_peers;
uint8_t device_sta_mac[6];
uint8_t peer_addresses[NETWORK_MAX_CONN][6];
uint8_t peers_in_mesh = 1; // 1 is us
uint8_t peer_mesh_position = 0;

esp_err_t esp_now_mesh_init(void){

    if(esp_now_init() != ZAIRE_OK) return ZAIRE_FAIL;

    ESP_ERROR_CHECK(esp_now_register_send_cb(esp_now_sent_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(esp_now_recv_cb));

    return ZAIRE_OK;

}

void send_data_to_mesh(uint8_t data){
    for(int i = 0; i < peers_in_mesh; i++){

        if(memcmp(peer_addresses[i], device_sta_mac, ESP_NOW_ETH_ALEN) != 0){
            esp_now_send(peer_addresses[i], &data, sizeof(&data));
        }

    }
}


void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status){

}

void esp_now_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len){

    switch (walkie_pairing_mode)
    {
    case NONE:
        switch (data_len){
        case 0x01:
            switch (data[0])
            {
                case WALKIE_PAIRING_START:
                    
                    peers_in_mesh = 0;
                    walkie_pairing_mode = SYNC;
                    break;

                case WALKIE_PAIRING_DONE:
                    walkie_pairing_close_down();
                    break;
                default:
                    break;
            }
            break;
        case 0x04:
            switch (data[0])
            {
            case WALKIE_REMOVE_PEER_P0:
                detach_peer_from_mesh(0x00);
                break;
            
            case WALKIE_REMOVE_PEER_P1:
                detach_peer_from_mesh(0x01);
                break;
            
            case WALKIE_REMOVE_PEER_P2:
                detach_peer_from_mesh(0x02);
                break;
            
            case WALKIE_REMOVE_PEER_P3:
                detach_peer_from_mesh(0x03);
                break;
            
            case WALKIE_REMOVE_PEER_P4:
                detach_peer_from_mesh(0x04);
                break;
            
            case WALKIE_REMOVE_PEER_P5:
                detach_peer_from_mesh(0x05);
                break;
            case WALKIE_REMOVE_PEER_P6:
                detach_peer_from_mesh(0x06);
                break;
            case WALKIE_REMOVE_PEER_P7:
                detach_peer_from_mesh(0x07);
                break;
            case WALKIE_REMOVE_PEER_P8:
                detach_peer_from_mesh(0x08);
                break;

            default:
                break;
            }
            break;
        default:
            printf("data: %d, len: %d\n", data[0], data_len);
            break;
        }

        break;

    case MASTER:
        if(data_len == 6){
            if(esp_now_is_peer_exist(data) == false){
                add_pairing_new_mesh(data);
            }
        }
        break;
    case SLAVE:
        if(data_len == 6){
            bool is_in_list = false;

            for(int i = 0; i < peers_in_mesh; i++){
                if(memcmp(peer_addresses[i], data, ESP_NOW_ETH_ALEN) == 0){
                    is_in_list = true;
                    break;
                }
            }

            if(is_in_list == false){
                esp_now_peer_info_t peer_info = {0};
                memcpy(peer_info.peer_addr, data, ESP_NOW_ETH_ALEN);
                peer_info.channel = ESP_NOW_CHANNEL;
                peer_info.encrypt = false;

                if (esp_now_add_peer(&peer_info) == ESP_OK) {
                    if (peers_in_mesh < NETWORK_MAX_CONN + 1) {
                        // Optional: give time for connection
                        vTaskDelay(pdMS_TO_TICKS(5));
                        esp_now_send( peer_info.peer_addr, device_sta_mac, sizeof(device_sta_mac));
                        esp_now_del_peer(peer_info.peer_addr);
                        walkie_pairing_mode = SYNC;
                        display_target = DISPLAY_SHOW_WALKIE_SYNC_SETTING;
                        new_peers +=1; 
                    } else {
                        // Max connections reached, remove peer
                        // walkie_pairing_max(data);
                    }
                }
            }
        }

        break;

    case SYNC:
        
        if(data_len == 6){
            walkie_pairing_sync_slave(data);
        }else if(data_len == 1){
            switch (data[0])
            {
                case WALKIE_PAIRING_START:
                    peers_in_mesh = 0;
                    break;

                case WALKIE_PAIRING_DONE:
                    walkie_pairing_close_down();
                    break;
                
                case WALKIE_PAIRING_CANCEL:
                    walkie_pairing_cancel_slave();
                    break;
                
                default:
                    break;
            }
        }
    
    default:
        
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
        esp_now_send(mac_addr, device_sta_mac, sizeof(device_sta_mac));
        vTaskDelay(pdMS_TO_TICKS(50));
        // remove from peer stack
        vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        esp_now_del_peer(mac_addr);

    }

}


void add_pairing_new_mesh(uint8_t *addr){
    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, addr, ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.encrypt = false;
   
    if (esp_now_add_peer(&peer_info) == ESP_OK) {
        if (peers_in_mesh < NETWORK_MAX_CONN) {
            memcpy(peer_addresses[peers_in_mesh], addr, ESP_NOW_ETH_ALEN);
            // Optional: give time for connection
            vTaskDelay(pdMS_TO_TICKS(5));
            // Send test byte
            peers_in_mesh +=1;
            new_peers += 1;
        }
    }
}

void peer_leave_mesh(void){
    
    switch (peer_mesh_position)
    {
    case 0x00:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P0);
        break;
    
    case 0x01:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P1);
        break;
    
    case 0x02:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P2);
        break;
    
    case 0x03:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P3);
        break;
    
    case 0x04:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P4);
        break;
    
    case 0x05:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P5);
        break;
    
    case 0x06:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P6);
        break;
    
    case 0x07:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P7);
        break;
    
        
    case 0x08:
        send_data_to_mesh(WALKIE_REMOVE_PEER_P8);
        break;
    
    
    default:
        break;
    }

    for(int i = 0; i < peers_in_mesh; i++){
        if(memcmp(peer_addresses[i], device_sta_mac, ESP_NOW_ETH_ALEN) != 0)esp_now_del_peer(peer_addresses[i]); //delete all peers connection
        memcpy(peer_addresses[i], device_sta_mac, ESP_NOW_ETH_ALEN); // remove everyone from list
    }
    peers_in_mesh = 1;
}

void detach_peer_from_mesh(uint8_t position){
    esp_now_del_peer(peer_addresses[position]); //remove from mesh
    memcpy(peer_addresses[position], device_sta_mac, ESP_NOW_ETH_ALEN); // set deleted postion to device's STA will be skipped whenenever peer_addresses is called
    // Not touching peer_in_mesh
    printf("Remove %d\n", position);
}
