#include <globalVar.h>





void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status){

    if(status == ESP_NOW_SEND_SUCCESS){
       top_led_state = LED_BLINK_FAST;
    } else {
        top_led_state = LED_OFF;
    }
}


esp_now_recv_cb_t esp_now_recv_cb(const uint8_t *mac_addr,  const uint8_t *data, int data_len){
    // Placeholder for actual ESP-NOW receive callback code
    // This function should handle the received data
    return ESP_OK;
}


void remote_pairing(void){

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
                
                request_sta_mac_addr(ap_info[i].bssid); // Request STA MAC address from the AP
                break;
            }
        }
       
    }

}

void request_sta_mac_addr(uint8_t *mac_addr){
    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, mac_addr, ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.encrypt = false;

    if (esp_now_add_peer(&peer_info) == ESP_OK) {
         // Set top LED to fast blink state
        // Request STA
        vTaskDelay(pdMS_TO_TICKS(100));
        uint8_t msg = REMOTE_REQUEST_STA_MAC;
        esp_now_send(mac_addr,12, sizeof(12));
    
    }
}