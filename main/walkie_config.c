#include <globalVar.h>

walkie_pairing_mode_t walkie_pairing_mode = NONE;
bool is_walkie_in_pairing_session = false;

esp_err_t init_walkie(void){

    if(i2s_init() != ZAIRE_OK)return ZAIRE_FAIL;

    return ZAIRE_OK;
}

void walkie_pairing_sequence(void){
        //Enter host pairing mode
        display_en = true;
        display_target = DISPLAY_SHOW_WALKIE_MASTER_SETTING;
        
        double_quick_buzz();
        vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY+500)); // a bit longer this time
        if(gpio_get_level(WALKIE_BTN) == HIGH){
            //Enter slave pairing mode
            display_target = DISPLAY_SHOW_WALKIE_SLAVE_SETTING;
            double_quick_buzz();
            vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
            if(gpio_get_level(WALKIE_BTN) == HIGH){
                //Cancle pairing request
                display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
                quick_buzz();
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                display_off();
            }else{
                
                walkie_pairing_slave();
            }
        }else{
            
            walkie_pairing_master();
        }
        vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
}

void walkie_pairing_master(void){
    if(is_walkie_in_pairing_session == false){    
        display_target = DISPLAY_SHOW_WALKIE_MASTER_SEARCH_SETTING;
        walkie_pairing_mode = MASTER;
        display_special_on = true;
        display_en = true;
        is_walkie_in_pairing_session = true;
        network_pairing_mode_master();

        while (walkie_pairing_mode == MASTER)
        {
            if(gpio_get_level(WALKIE_BTN) == HIGH)break;
            walkie_discover_peers();
            vTaskDelay(pdMS_TO_TICKS(10));

        }
        vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        network_standard_mode();

        if(new_peers > 0){
            walkie_pairing_sync_master();
            display_target = DISPLAY_SHOW_WALKIE_PAIRED_SETTING;
            walkie_pairing_mode = NONE;
            quick_buzz();
            vTaskDelay(pdMS_TO_TICKS(1500));
            walkie_pairing_close_down();
        }else{
            display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
            walkie_pairing_mode = NONE;
            quick_buzz();
            vTaskDelay(pdMS_TO_TICKS(1000));
            
        }
    }else{
        display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
        walkie_pairing_mode = NONE;
        quick_buzz();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    //Pairing close down
    display_special_on = false;
    is_walkie_in_pairing_session = false;
}

void walkie_pairing_slave(void){    
    display_target = DISPLAY_SHOW_WALKIE_SLAVE_SEARCH_SETTING;
    walkie_pairing_mode = SLAVE;
    display_special_on = true;
    network_pairing_mode_slave();
    while (walkie_pairing_mode == SLAVE){
        if(gpio_get_level(WALKIE_BTN))break; //Canel pairing
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
    vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
    network_standard_mode();
    
    if(new_peers == 0){
        display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
        walkie_pairing_mode = NONE;
        quick_buzz();
        vTaskDelay(pdMS_TO_TICKS(1000));
        display_off();
    }

    while (walkie_pairing_mode == SYNC){ // AWAIT SYNC if we are paired to host
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    new_peers = 0; // Reset new_peers
    display_special_on = false;
}

void walkie_pairing_sync_master(void){
    display_target = DISPLAY_SHOW_WALKIE_SYNC_SETTING;
    walkie_pairing_mode = SYNC;
    double_quick_buzz();
    vTaskDelay(pdMS_TO_TICKS(1000));
    if(is_walkie_on == true){
        is_walkie_mute = true;
    }

    if(gpio_get_level(WALKIE_BTN) == LOW){ //If user wants to cancel pairing after finding new peer

        for(int i = 0; i < peers_in_mesh; i++){
            if(memcmp(peer_addresses[i],device_sta_mac,ESP_NOW_ETH_ALEN) != 0){ // chech it is not us

                uint8_t _start = WALKIE_PAIRING_START;
                esp_now_send(peer_addresses[i], &_start,sizeof(_start));
                
                for(int j = 0; j < peers_in_mesh; j++){
                    esp_now_send(peer_addresses[i],peer_addresses[j],sizeof(peer_addresses[j]));
                    vTaskDelay(pdMS_TO_TICKS(100)); // slow down a bit
                }

                uint8_t _done = WALKIE_PAIRING_DONE;
                esp_now_send(peer_addresses[i], &_done,sizeof(_done));
            
            }else{
                peer_mesh_position = i;
            }
            vTaskDelay(pdMS_TO_TICKS(10)); // let header breath
                
        }
        is_walkie_on = true;
        is_walkie_mute = false;
    }else{
        walkie_pairing_cancel_master();
    }

}

void walkie_pairing_sync_slave(uint8_t *addr){

    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, addr, ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.encrypt = false;

    if(memcmp(device_sta_mac, peer_info.peer_addr, ESP_NOW_ETH_ALEN) != 0){
        if(esp_now_is_peer_exist(peer_info.peer_addr) != true){
            esp_now_add_peer(&peer_info);
        }
    }else{
        peer_mesh_position = peers_in_mesh;
    }

    if (peers_in_mesh < NETWORK_MAX_CONN + 1) {
        // Optional: give time for connection
        vTaskDelay(pdMS_TO_TICKS(5));
        memcpy(peer_addresses[peers_in_mesh], peer_info.peer_addr, ESP_NOW_ETH_ALEN);
        peers_in_mesh +=1;
        is_walkie_on = true;
        is_walkie_mute = false;

    } else {
        // Max connections reached, remove peer
        // walkie_pairing_max(data);
    }

    
}

void walkie_pairing_close_down(void){ 
    walkie_pairing_mode = NONE;
    new_peers = 0;
    display_off();
}

void walkie_pairing_cancel_master(void){ 
    display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
    walkie_pairing_mode = NONE;
    vTaskDelay(pdMS_TO_TICKS(1000));

    uint8_t index = 0;
    while (new_peers > 0)
        {
            index = (peers_in_mesh + new_peers) - 1; //Index from back to front

            if(memcmp(peer_addresses[index],device_sta_mac, ESP_NOW_ETH_ALEN) != 0){
                uint8_t _end = WALKIE_PAIRING_CANCEL;
                esp_now_send(peer_addresses[index], &_end,sizeof(_end));
                vTaskDelay(pdMS_TO_TICKS(100));
                esp_now_del_peer(peer_addresses[index]);
                vTaskDelay(pdMS_TO_TICKS(50));
                new_peers -=1;
            }
        }
    
    new_peers = 0;
    walkie_pairing_close_down();

}

void walkie_pairing_cancel_slave(void){
    display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
    walkie_pairing_mode = NONE;
    vTaskDelay(pdMS_TO_TICKS(1000));
    walkie_pairing_close_down();
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
                for(int j = 0; j < peers_in_mesh; j++){
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

void walkie_mute(void){

    if(is_walkie_on == true){
        if(is_walkie_mute == false){
            quick_buzz();
            is_walkie_mute = true;
        }else{
            quick_buzz();
            is_walkie_mute = false;
        }

        display_show_walkie_mute_sequence();
        vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
        display_off();
    }

}

void walkie_sendData(const uint8_t *data, uint16_t len){
    while (!sendOver) {
        vTaskDelay(pdMS_TO_TICKS(10));  // Wait with delay to reduce CPU load
    }
    sendOver = false;
    for(int peer = 0; peer < peers_in_mesh; peer++){
        if(memcmp(peer_addresses[peer], device_sta_mac, ESP_NOW_ETH_ALEN) != 0){
            esp_now_send(peer_addresses[peer], data, len);
        }
    }
}