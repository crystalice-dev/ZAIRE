#include "globalVar.h"

bool walkie_get_addr_port = 0;
bool bt_read_data_raw = 0;
bool walkie_read_data_raw = 0;
bool pi_read_data_raw = 0;

int uart_init(void){
    esp_err_t err0;
    esp_err_t err1;
    esp_err_t err2;
    //WALKIE UART CONFIG
    uart_config_t walkie_uart_config = {
        .baud_rate = WALKIE_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_config_t bm83_uart_config = {
        .baud_rate = BM83_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    // Install WALKIE UART driver and set UART pins
    err0 = uart_driver_install(WALKIE_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(WALKIE_UART_NUM, &walkie_uart_config);
    err2 = uart_set_pin(WALKIE_UART_NUM, WALKIE_UART_TX, WALKIE_UART_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    if( err0 == ESP_FAIL || err1 == ESP_FAIL || err2 == ESP_FAIL){
        return ESP_FAIL;
    }

    // Install WALKIE UART driver and set UART pins
    // err0 = uart_driver_install(BM83_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    // err1 = uart_param_config(BM83_UART_NUM, &bm83_uart_config);
    // err2 = uart_set_pin(BM83_UART_NUM, BM83_UART_TX, BM83_UART_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    // if( err0 == ESP_FAIL || err1 == ESP_FAIL || err2 == ESP_FAIL){
    //     return ESP_FAIL; 
    // }

    return ESP_OK;

}

void bm83_uart_snd(const char *data){

}

void bm83_uart_rec(const char *data){

}


void walkie_uart_handler_int(uint8_t data){
    if(walkie_get_addr_port == 1 && walkie_interject_number < 6){
        walkie_address[walkie_interject_number] = data;
        walkie_interject_number +=1;
        if(walkie_interject_number == 6){
            walkie_get_addr_port = 0;
        }
    }else if(walkie_interject_number > 5){
        
    }
}


void walkie_uart_snd(const int data){
    char str[6];
    sprintf(str, "%d\n", data); // Convert data from int to str
    uart_write_bytes(WALKIE_UART_NUM, str, strlen(str)); // Send data
    vTaskDelay(pdMS_TO_TICKS(50));// Watchdog

}

void walkie_uart_rec(const char *str){

    int data = atoi(str); // Convert data from str to int

    switch (data){

        case RESTARTING_DEVICE: // System restarting -- system check failed
                esp_restart();
                break;
        case OPEN_ADDR_INSERT: // Will run only once during helmet's lifetime
            walkie_get_addr_port = 1;
            printf("PORT OPENED\n");
            break;

        case CLOSE_ADDR_INSERT: // Will run only once during helmet's lifetime
            walkie_get_addr_port = 0;
            break;

        case SET_WALKIE_ADDR: // Will run only once during helmet's lifetime
            printf("closing walkie addr port process\n");
            if(walkie_get_addr_port == 0 && walkie_interject_number == 6){
                esp_err_t err = nvs_set_blob(walkie_addr_nvs_registered, WALKIE_NVS_NAMESPACE, walkie_address, 6); // Store 6 bytes
                if(err == ESP_OK){
                    if(!nvs_write(walkie_addr_nvs_registered, WALKIE_ADDR_KEY, 1)){

                        size_t temp = sizeof(walkie_address); // Ensure temp has the correct size of the buffer
                        esp_err_t err = nvs_get_blob(walkie_addr_nvs_registered, WALKIE_NVS_NAMESPACE, walkie_address, &temp); // Pass the address of temp
                        if(err == ESP_OK){
                            walkie_interject_number = 6; // Ensure walkie mac addr never changes
                            for(int i = 0; i < 6; i++){
                                printf("0x%02X", walkie_address[i]);
                                if(i < 5){
                                    printf(":");
                                }
                            }
                            printf("\n");
                        }

                    }
                }
            }

            walkie_uart_snd(CLOSE_ADDR_INSERT);

            break;

        case OPENED_SETTING_PORT:
            printf("SETTINGS PORT OPENED\n");

        default:
        walkie_uart_handler_int(data);
        break;
    }
    

}