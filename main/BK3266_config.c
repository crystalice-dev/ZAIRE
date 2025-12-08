#include <globalVar.h>


bool is_bk3266_on = false;

esp_err_t init_bk3266(void){
    bk3266_send_cmd(BK3266_EN_CALL);
    bk3266_send_cmd(BK3266_SET_STEREO);
    bk3266_send_cmd(BK3266_SET_EQ);
    return ZAIRE_OK;
}

void bk3266_send_cmd(const char *cmd) {
    uart_write_bytes(BK3266_UART_NUM, cmd, strlen(cmd));
    vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
    uart_clear_intr_status(BK3266_UART_NUM,sizeof(cmd));
}

void bk3266_set_bt_name(const char *name){
    char new_name[128];
    snprintf(new_name, sizeof(new_name), "RECV+SNAME+%s", name);
    bk3266_send_cmd(new_name);
}

void bk3266_PP_CALL(void){
    gpio_set_level(BK3266_PP_CALL, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_level(BK3266_PP_CALL, LOW);
    vTaskDelay(pdMS_TO_TICKS(100));

}
