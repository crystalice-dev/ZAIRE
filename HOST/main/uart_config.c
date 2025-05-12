#include <globalVar.h>



esp_err_t uart_init(void){

    esp_err_t err0, err1, err2;

    uart_config_t uart_config = {
        .baud_rate = 9600,  // NEO-6M default
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    err0 = uart_driver_install(GPS_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(GPS_UART_NUM, &uart_config); 
    err2 = uart_set_pin(GPS_UART_NUM, GPS_TX, GPS_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    if(err0 != ESP_OK || err1 != ESP_OK || err2 != ESP_OK){
        printf("GPS NOT ACTIVATED\n");
        return ESP_FAIL;
    }
    printf("GPS  ACTIVATED\n");

    return ESP_OK;
}