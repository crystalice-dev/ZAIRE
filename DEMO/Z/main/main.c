#include "globalVar.h"




void app_main(){
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    

    gpio_pin_init();
    buzzer_init();
    bs_monitor_init();

    #ifdef DISPLAY_INCLUDED
        display_init();
    #endif   
    //tasks
    xTaskCreate(gpio_purpose_run_task, "GPIO PURPOSE TASK", 5120, NULL, 4, &gpio_purpose_btn_task_handler);
    xTaskCreate(gpio_walkie_run_task, "GPIO WALKIE TASK", 5120, NULL, 4, &gpio_walkie_btn_task_handler);
    xTaskCreate(bs_left_monitor_task, "bs_left_monitor_task", 4096, NULL, 7,&bs_left_monitor_handler);
    xTaskCreate(bs_right_monitor_task, "bs_right_monitor_task", 4096, NULL, 7,&bs_right_monitor_handler);
    xTaskCreate(walkie_run_task, "BK TASK", 4096, NULL, 7, &walkie_task_handler);

    #ifdef LIGHTS_INCLUDED
        xTaskCreate(led_strip_run_task, "LED STRIP TASK", 4096, NULL, 2, &led_strip_task_handler);
    #endif

    #ifdef DISPLAY_INCLUDED
        xTaskCreate(display_run_task, "DISPLAY TASK", 2048, NULL, 2, &display_task_handler);
    #endif

   #ifdef DISPLAY_INCLUDED
        vTaskDelay(pdMS_TO_TICKS(5000));
        display_target = DISPLAY_EN_OFF;
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(DISPLAY_EN_PIN, LOW);
    #endif
}