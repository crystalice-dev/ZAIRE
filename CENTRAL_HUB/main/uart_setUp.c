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
    err0 = uart_driver_install(BM83_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    err1 = uart_param_config(BM83_UART_NUM, &walkie_uart_config);
    err2 = uart_set_pin(BM83_UART_NUM, BM83_UART_TX, BM83_UART_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    if( err0 == ESP_FAIL || err1 == ESP_FAIL || err2 == ESP_FAIL){
        return ESP_FAIL; 
    }

    return ESP_OK;

}

void bm83_uart_snd(const char *data){

}

void bm83_uart_rec(const char *data){

}

void walkie_uart_snd(const char *data){
    uart_write_bytes(WALKIE_UART_NUM, data, strlen(data));
    vTaskDelay(pdMS_TO_TICKS(10));// Watchdog

}

void walkie_uart_rec(const char *data){

    if(walkie_read_data_raw == 1){

   }else{
    uint8_t value = (uint8_t)strtol(data, NULL, 16);
    switch (value)
    {
    case OPEN_ADDR_INSERT:
        walkie_get_addr_port = 1;
        break;
    case CLOSE_ADDR_INSERT:
        walkie_get_addr_port = 0;
    case SET_WALKIE_ADDR:
        esp_err_t err = nvs_set_blob(walkie_addr_nvs_registered, WALKIE_NVS_NAMESPACE, walkie_address, 6); // Store 6 bytes
        if(err == ESP_OK){
            nvs_write(walkie_addr_nvs_registered, WALKIE_ADDR_KEY, 1);
        }
    default:
        //walkie_uart_handler_int(value);
        break;
    }
    
   }


}