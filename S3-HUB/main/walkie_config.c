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
    while (1){
        if(gpio_get_level(WALKIE_BTN)){
            host_uart_write_str(WALKIE_PAIRING_COMPLETE);
            break;
        }
        walkie_discover_peers();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void walkie_pairing_slave(void){
    while (1){
        if(gpio_get_level(WALKIE_BTN)){
            host_uart_write_str(WALKIE_PAIRING_COMPLETE);
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void walkie_pairing_sync(void){
   
}


