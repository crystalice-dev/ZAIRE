#include <globalVar.h>





void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status){

}


esp_now_recv_cb_t esp_now_recv_cb(const uint8_t *mac_addr,  const uint8_t *data, int data_len){
    // Placeholder for actual ESP-NOW receive callback code
    // This function should handle the received data
    return ESP_OK;
}