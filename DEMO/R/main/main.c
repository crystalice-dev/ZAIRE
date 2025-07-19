#include "globalVar.h"

bool pairing_mode = 0;

void app_main(){

    esp_err_t ret;
    // Initialize NVS -- ALWAYS FIRST
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(gpio_init());

    xTaskCreate(gpio_top_btn_run_task, "gpio_top_btn_task", 4096, NULL, 5, &gpio_top_btn_task_handler);
    xTaskCreate(gpio_left_btn_run_task, "gpio_left_btn_task", 2048, NULL, 5, &gpio_left_btn_task_handler);
    xTaskCreate(gpio_right_btn_run_task, "gpio_right_btn_task", 2048, NULL, 5, &gpio_right_btn_task_handler);
    xTaskCreate(gpio_left_led_run_task, "gpio_left_led_task", 2048, NULL, 5, &gpio_left_led_task_handler);
    xTaskCreate(gpio_right_led_run_task, "gpio_right_led_task", 2048, NULL, 5, &gpio_right_led_task_handler);
    xTaskCreate(gpio_top_led_run_task, "gpio_top_led_task", 2048, NULL, 5, &gpio_top_led_task_handler);
    // Start the FreeRTOS scheduler

}