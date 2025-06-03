#include <globalVar.h>



esp_err_t uart_init(void){

    esp_err_t err0, err1, err2;

    uart_config_t host_uart_config = {
        .baud_rate = HOST_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    err0 = uart_driver_install(HOST_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(HOST_UART_NUM, &host_uart_config); 
    err2 = uart_set_pin(HOST_UART_NUM, HOST_TX, HOST_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    if(err0 != ESP_OK || err1 != ESP_OK || err2 != ESP_OK){
        return ESP_FAIL;
    }

    // uart_config_t h3_uart_config = {
    //     .baud_rate = H3_BAUD,
    //     .data_bits = UART_DATA_8_BITS,
    //     .parity    = UART_PARITY_DISABLE,
    //     .stop_bits = UART_STOP_BITS_1,
    //     .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    // };

    // err0 = uart_driver_install(H3_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    // err1 = uart_param_config(H3_UART_NUM, &h3_uart_config); 
    // err2 = uart_set_pin(H3_UART_NUM, H3_TX, H3_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // if(err0 != ESP_OK || err1 != ESP_OK || err2 != ESP_OK){
    //     return ESP_FAIL;
    // }

    uart_config_t bk_uart_config = {
        .baud_rate = BK_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    err0 = uart_driver_install(AUDIO_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(AUDIO_UART_NUM, &bk_uart_config); 
    err2 = uart_set_pin(AUDIO_UART_NUM, BK_TX, BK_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    if(err0 != ESP_OK || err1 != ESP_OK || err2 != ESP_OK){
        return ESP_FAIL;
    }

    return ESP_OK;
}


void host_uart_received(const char* str){
    if (str[0] == AUDIO_PLAYER_TARGET) {
        if(str[1] == AUDIO_PLAYER_TARGET_NAME){
            const char *name = strchr(str, ':');
            if (name && *(name + 1) != '\0') {
                name++;  // Move past the colon
                bk_set_device_name(name);
            }
        }else{
            int value = atoi(&str[1]);  // Pass pointer to the string starting at str[1]
            audio_chip_uart_handler(value);
        }
    }
}

void host_uart_write_str(const char* str){
    uart_write_bytes(HOST_UART_NUM, str, strlen(str));
    vTaskDelay(pdMS_TO_TICKS(250));
    
}

void host_uart_write_int(int data){
}

void bk_uart_snd(const char* str){
    uart_write_bytes(AUDIO_UART_NUM, str, strlen(str));
    vTaskDelay(pdMS_TO_TICKS(50));
    uart_flush(AUDIO_UART_NUM);

}

void bk_uart_received(const char* str){
    if(memcmp(str,"+OK",3) == 0){
        printf("same\n");
    }
    printf("%s\n", str);
}