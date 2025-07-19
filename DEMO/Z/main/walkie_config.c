#include "globalVar.h"

bool sendOver=0;
bool recOver=0;
bool speakOut=0;
bool walkie_mute=0;
bool walkie_paired=0;


void walkie_pairing_master(void){

    //master_reconfig();
    while (walkie_pairing_mode == MASTER){
        if(gpio_get_level(WALKIE_BTN)){
            led_target_stage = SYNC_PAIRING;
            vTaskDelay(pdMS_TO_TICKS(5000));
            break;
        }
        // walkie_discover_peers();
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    // if(new_peers > 0){
    //     host_uart_write_str(WALKIE_PAIRING_SYNC);
    //     for(int i = 0; i < number_paired_peers; i++){
    //         if(memcmp(peer_addresses[i],device_sta_mac,ESP_NOW_ETH_ALEN) != 0){ // chech it is not us
                
    //             for(int j = 0; j < number_paired_peers; j++){
    //                 esp_now_send(peer_addresses[i],peer_addresses[j],sizeof(peer_addresses[j]));
    //                 vTaskDelay(pdMS_TO_TICKS(50)); // slow down a bit
    //             }
    //             uint8_t msg = WALKIE_PAIRING_DONE;
    //             esp_now_send(peer_addresses[i], &msg,sizeof(msg));
    //         }
            
    //     }
    // }

    // station_reconfig();
    walkie_paired = 1;
    number_paired_peers += 1;
    printf("%d\n", number_paired_peers);
    led_target_stage = NORMAL;
    display_target = DISPLAY_MAIN_UI;
    gpio_set_level(DISPLAY_EN_PIN, HIGH);
    quick_buzz();
    vTaskDelay(pdMS_TO_TICKS(3000));
    display_target = DISPLAY_EN_OFF;
    vTaskDelay(pdMS_TO_TICKS(500));
    gpio_set_level(DISPLAY_EN_PIN, LOW);
    
}