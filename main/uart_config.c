#include <globlaVar.h>


esp_err_t init_uart(){

    const uart_config_t cfg = {
        .baud_rate = BK3266_UART_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    if(uart_param_config(BK3266_UART_NUM, &cfg) != ZAIRE_OK) return ZAIRE_FAIL;
    if(uart_set_pin(BK3266_UART_NUM, BK3266_UART_TX, BK3266_UART_RX,
                        UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ZAIRE_OK) return ZAIRE_FAIL;
    if(uart_driver_install(BK3266_UART_NUM, RX_BUF_SIZE, 0, 0, NULL, 0) != ZAIRE_OK) return ZAIRE_FAIL;

    return ZAIRE_OK;
}

