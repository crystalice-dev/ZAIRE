#include <globalVar.h>



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

}

void walkie_uart_write_str(const char* str){

}

void walkie_uart_write_int(int data){

}
