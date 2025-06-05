#include <globalVar.h>

TaskHandle_t gpio_task_handler = NULL;
TaskHandle_t host_task_handler = NULL;
TaskHandle_t bk_task_handler = NULL;
TaskHandle_t h3_task_handler = NULL;
TaskHandle_t i2c_task_handler = NULL;
TaskHandle_t walkie_task_handler = NULL;

void gpio_run_task(void *vpParam){

    while (1)
    {
        if(gpio_get_level(WALKIE_BTN) == HIGH){
            vTaskDelay(pdMS_TO_TICKS(250));
            if(gpio_get_level(WALKIE_BTN) == HIGH){
                speakOut = 1;
            }else{
                vTaskDelay(pdMS_TO_TICKS(500));
                if(gpio_get_level(WALKIE_BTN) == HIGH){
                    host_uart_write_str(WALKIE_PAIRING_MASTER); // SEND COMMAND FOR LIGHTS
                    printf("master\n");
                    vTaskDelay(pdMS_TO_TICKS(2000));
                    if(gpio_get_level(WALKIE_BTN) == 1){
                        host_uart_write_str(WALKIE_PAIRING_SLAVE); // SEND COMMAND FOR LIGHTS
                        printf("slave\n");
                        vTaskDelay(pdMS_TO_TICKS(2000));
                        if(gpio_get_level(WALKIE_BTN) == 1){
                            host_uart_write_str(WALKIE_PAIRING_COMPLETE); // SEND COMMAND FOR LIGHTS
                        }else{
                            // LAUNCH SLAVE PAIRING HERE
                            walkie_pairing_mode = SLAVE;
                            walkie_pairing_slave();
                        }
                    }else{
                        // LAUNCH MASTER PAIRING HERE
                        walkie_pairing_mode = MASTER;
                        walkie_pairing_master();
                    }
                    vTaskDelay(pdMS_TO_TICKS(2000));
                    station_reconfig();
                    new_peers = 0;
                    walkie_pairing_mode = NONE;
                    host_uart_write_str(WALKIE_PAIRING_COMPLETE);
                }else{
                    if(speakOut == 1){
                        speakOut = 0;
                    }else{
                        
                        if(number_paired_peers > 1){
                            
                            printf("MUTE WALKIE\n");
                        }
                    }
                }
            }
        }else{
                speakOut = 0;
            }
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    

}

void host_run_task(void *vpParam) {
    uint8_t host_data[BUF_SIZE];

    while (1) {
        // Read from HOST UART
        int host_len = uart_read_bytes(HOST_UART_NUM, host_data, BUF_SIZE, pdMS_TO_TICKS(100));

        if (host_len > 0) {
            // Directly write the raw bytes to H3 UART
            host_uart_received((const char *)host_data);

            // Optional: flush output if needed
            // uart_wait_tx_done(H3_UART_NUM, pdMS_TO_TICKS(50));

            // Optional: log received data as null-terminated string
            if (host_len < BUF_SIZE) host_data[host_len] = '\0';
            // printf("Forwarded: %s\n", (char *)host_data);
        }

        // Prevent CPU hogging (adjust delay as needed)
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}


void bk_run_task(void *vpParam) {
    uint8_t bk_data[BUF_SIZE];

    while (1) {
        int bk_len = uart_read_bytes(AUDIO_UART_NUM, bk_data, BUF_SIZE, pdMS_TO_TICKS(100));

        if (bk_len > 0) {
            // Directly write the raw bytes to H3 UART
            bk_uart_received((const char *)bk_data);

            // Optional: log received data as null-terminated string
            if (bk_len < BUF_SIZE) bk_data[bk_len] = '\0';
            // printf("Forwarded: %s\n", (char *)host_data);
        }

        // Prevent CPU hogging (adjust delay as needed)
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}


void h3_run_task(void *vpParam) {
    uint8_t h3_data[BUF_SIZE];

    while (1) {
        // Read from HOST UART
        int host_len = uart_read_bytes(H3_UART_NUM, h3_data, BUF_SIZE, pdMS_TO_TICKS(100));

        if (host_len > 0) {
            printf("%s\n",(const char *)h3_data);

            // Optional: log received data as null-terminated string
            if (host_len < BUF_SIZE) h3_data[host_len] = '\0';
            // printf("Forwarded: %s\n", (char *)host_data);
        }

        // Prevent CPU hogging (adjust delay as needed)
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void walkie_run_task(void *vpParam){

    while (1)
    {
        if(speakOut == 1){
            walkie_snt(1);
            vTaskDelay(pdMS_TO_TICKS(28));
        }
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    
} 

