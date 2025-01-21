#include "globalVar.h"



void gpio_run_task(void *vpParam){ // Watches for GPIO changes - btn pressed - camera on - read/write sdCard

    while (1)
    {   
      
        if(first_boot && gpio_get_level(PURPOSE_BTN_L) && gpio_get_level(PURPOSE_BTN_R)){
            gpio_set_level(PURPOSE_LED, HIGH);
            vTaskDelay(pdMS_TO_TICKS(1500)); // wait 1.5 sec to launch settings
            walkie_uart_snd(OPEN_SETTING_PORT);
        }else{
            first_boot = 0;
        }
        
        vTaskDelay(pdMS_TO_TICKS(50));
    }
    
}

void uart_run_task(void *vpParam){

    uint8_t walkie_data[BUF_SIZE];
    uint8_t bm83_data[BUF_SIZE];

    while (1)
    {
         // Read and process Walkie UART data
        int walkie_len = uart_read_bytes(WALKIE_UART_NUM, walkie_data, BUF_SIZE, pdMS_TO_TICKS(100));
        if (walkie_len > 0) {
            walkie_uart_rec((const char *)walkie_data);
            memset(walkie_data, 0, sizeof(walkie_data));  // Clears the buffer
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
    
}