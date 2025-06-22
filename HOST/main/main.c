/*
    TITLE: S2-HUB
    DESC: Serves web content in APSTA mode with captive portal DNS hijack
*/

#include <globalVar.h>



void app_main(void){

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    if(zaire_system_check() == ESP_FAIL){
        ESP_LOGE("INIT", "Failed to Init Zaire Helmets System");
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_restart();
    }

    
    #if DEVICE_TYPE != DEVICE_TYPE_TEST
        xTaskCreate(gpio_run_task, "GPIO TASK", 5120, NULL, 4, &gpio_task_handler);
        xTaskCreate(gps_uart_run_task, "UART TASK", 10000, NULL, 10, &gps_uart_task_handler);
        xTaskCreate(h3_uart_run_task, "UART TASK", 10000, NULL, 10, &h3_uart_task_handler);
        xTaskCreate(walkie_uart_run_task, "UART TASK", 10000, NULL, 10, &walkie_uart_task_handler);
        xTaskCreate(i2c_run_task, "I2C TASK", 4096,NULL, 1, &i2c_task_handler);

    #else
        xTaskCreate(test_run_task, "TEST TASK", 4096, NULL, 7, NULL);

    #endif

    #ifdef BUZZER_INCLUDED
        buzzer_init();
    #endif

    #ifdef LIGHTS_INCLUDED
        xTaskCreate(led_strip_run_task, "LED STRIP TASK", 4096, NULL, 2, &led_strip_task_handler);
    #endif

    // #ifdef DISPLAY_INCLUDED
    //     xTaskCreate(display_run_task, "DISPLAY TASK", 2048, NULL, 2, &display_task_handler);
    // #endif

    #ifdef BLINDSPOT_INCLUDED
        xTaskCreate(bs_right_monitor_task, "BLINDSPOT TASK RIGHT", 2048, NULL, 7, &bs_right_monitor_handler);
        xTaskCreate(bs_left_monitor_task, "BLINDSPOT TASK LEFT", 2048, NULL,7, &bs_left_monitor_handler);
    #endif


    // if(battery_init() == ESP_OK){
    //     float v = battery_get_voltage();
    //     float soc = battery_get_soc();
    //     printf("Battery: %.2f V | %.0f%%\n", v, soc);
    // }else{
    //     printf("Could not init bat\n");
    // }

    

    //Last roll out
    // #ifdef DISPLAY_INCLUDED
    //     vTaskDelay(pdMS_TO_TICKS(3000));
    //     display_target = DISPLAY_EN_OFF;
    //     vTaskDelay(pdMS_TO_TICKS(500));
    //     gpio_set_level(DISPLAY_EN_PIN, LOW);
    // #endif

}

