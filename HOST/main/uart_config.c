#include <globalVar.h>

uart_data_type_t uart_data_type = IMG; // Default to standard data type


esp_err_t uart_init(void){

    esp_err_t err0, err1, err2;

    uart_config_t gps_uart_config = {
        .baud_rate = GPS_BAUD,  // NEO-6M default
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    err0 = uart_driver_install(GPS_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(GPS_UART_NUM, &gps_uart_config); 
    err2 = uart_set_pin(GPS_UART_NUM, GPS_TX, GPS_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    if(err0 != ESP_OK || err1 != ESP_OK || err2 != ESP_OK){

        return ESP_FAIL;
    }

    uart_config_t walkie_uart_config = {
        .baud_rate = WALKIE_BAUD,  
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    err0 = uart_driver_install(WALKIE_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(WALKIE_UART_NUM, &walkie_uart_config); 
    err2 = uart_set_pin(WALKIE_UART_NUM, WALKIE_TX, WALKIE_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    if(err0 != ESP_OK || err1 != ESP_OK || err2 != ESP_OK){

        return ESP_FAIL;
    }

    uart_config_t h3_uart_config = {
        .baud_rate = H3_BAUD,  
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    err0 = uart_driver_install(H3_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(H3_UART_NUM, &h3_uart_config); 
    err2 = uart_set_pin(H3_UART_NUM, H3_TX, H3_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    if(err0 != ESP_OK || err1 != ESP_OK || err2 != ESP_OK){

        return ESP_FAIL;
    }

    return ESP_OK;
}

void walkie_uart_received(const char* str){
    char c = str[1];
    int n = c - '0'; // Only works for '0' to '9'
    
    if(str[0] == 'P'){
        switch (n)
        {
            case 0:
                led_target_stage = MASTER_PAIRING;
                break;
            case 1:
                led_target_stage = SLAVE_PAIRING;
                break;
            case 2:
                led_target_stage = SYNC_PAIRING;
                break;
            default:
                led_target_stage = NORMAL;
                break;
        }
    }else if(str[0] == 'B'){
        switch (n)
        {
        case 1:
            quick_buzz();
            break;
        case 0:
            double_quick_buzz();
            break;
        
        default:
            break;
        }
    }

}

void walkie_uart_send_data(const char* str){
    // This function is used to send data to the Walkie UART
    // It can be used for debugging or sending status messages
    uart_write_bytes(WALKIE_UART_NUM, str, strlen(str));
    vTaskDelay(pdMS_TO_TICKS(100)); // Ensure the data is sent before proceeding
}

void h3_uart_send_data(const char* str){
    // This function is used to send data to the h3 via UART
    // It can be used for debugging or sending status messages
    uart_write_bytes(H3_UART_NUM, str, strlen(str));
    uart_flush(H3_UART_NUM);
    vTaskDelay(pdMS_TO_TICKS(100)); // Ensure the data is sent before proceeding
}

void h3_uart_received(const char* str){
    if(strlen(str) < 6){
        if(str[0] == 'D'){
            if(str[2] == 'R'){
                wifi_send_ap_bssid();
            }
        }
    }
}