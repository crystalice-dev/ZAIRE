#include <globalVar.h>




void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status){

}

esp_now_recv_cb_t esp_now_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len){
    
    if(remote_pairing_requested_btn == 1){
        if(data_len < 6){
            if(data[0] == REMOTE_REQUEST_STA_MAC && device_sta_mac_requested == 0){
                device_sta_mac_requested = 1;
            }
        }else{
            if(device_sta_mac_requested == 1){
                
                uint8_t mac[6];
                esp_wifi_get_mac(WIFI_IF_STA, mac);
                esp_now_peer_info_t peer_info = {0};
                memcpy(peer_info.peer_addr, data, ESP_NOW_ETH_ALEN);
                peer_info.channel = 7;
                peer_info.encrypt = false;
                vTaskDelay(pdMS_TO_TICKS(100));
                esp_now_send(data, mac, sizeof(mac));

            }
        }
    }else{

    }
    return ESP_OK;
}
