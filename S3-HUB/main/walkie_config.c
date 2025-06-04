#include <globalVar.h>


bool sendOver=1;
bool recOver=0;
bool speakOut=0;
int32_t *samples_32bit;
int16_t *samples_16bit;
uint8_t *samples_8bit ;
int16_t *recive_16bit;
int16_t *output_16bit;



void walkie_pairing_master(void){
    while (walkie_pairing_mode == MASTER){
        if(gpio_get_level(WALKIE_BTN)){
            host_uart_write_str(WALKIE_PAIRING_COMPLETE);
            break;
        }
        walkie_discover_peers();
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    host_uart_write_str(WALKIE_PAIRING_SYNC);
    vTaskDelay(pdMS_TO_TICKS(2000));
    // station_reconfig();
    // for(int i = 0; i < number_paired_peers; i++){
    //     if(memcmp(peer_addresses[i],device_sta_mac,ESP_NOW_ETH_ALEN) != 0){ // chech it is not us
    //         for(int j = 0; j < number_paired_peers; j++){
    //             esp_now_send(peer_addresses[i],peer_addresses[j],sizeof(peer_addresses[j]));
    //             vTaskDelay(pdMS_TO_TICKS(50)); // slow down a bit
    //         }
    //         uint8_t msg = WALKIE_PAIRING_COMPLETE;
    //         esp_now_send(peer_addresses[i], msg,sizeof(msg));
    //     }
        
    // }
}

void walkie_pairing_slave(void){
    slave_reconfig();
    while (walkie_pairing_mode == SLAVE){
        if(gpio_get_level(WALKIE_BTN)){
            host_uart_write_str(WALKIE_PAIRING_COMPLETE);
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    host_uart_write_str(WALKIE_PAIRING_SYNC);
    station_reconfig();
}

void walkie_pairing_sync(uint8_t *addr){
    
    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, addr, ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.encrypt = false;

    if (esp_now_add_peer(&peer_info) == ESP_OK) {
        if (number_paired_peers < mesh_system_max_connection) {
            memcpy(peer_addresses[number_paired_peers], addr, ESP_NOW_ETH_ALEN);
            // Optional: give time for connection
            vTaskDelay(pdMS_TO_TICKS(5));
            number_paired_peers += 1;
        } else {
            // Max connections reached, remove peer
            walkie_pairing_max(addr);
        }
    }
}





