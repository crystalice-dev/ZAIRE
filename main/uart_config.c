#include <globalVar.h>


esp_err_t init_uart(){

    const uart_config_t h3_cfg = {
        .baud_rate = H3_UART_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    if(uart_param_config(H3_UART_NUM, &h3_cfg) != ZAIRE_OK) return ZAIRE_FAIL;
    if(uart_set_pin(H3_UART_NUM, H3_UART_TX, H3_UART_RX,
                        UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ZAIRE_OK) return ZAIRE_FAIL;
    if(uart_driver_install(H3_UART_NUM, RX_BUF_SIZE, 0, 0, NULL, 0) != ZAIRE_OK) return ZAIRE_FAIL;

    return ZAIRE_OK;
}

