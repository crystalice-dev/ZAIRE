/*
    TITLE: S2-HUB
    DESC: Serves web content in APSTA mode with captive portal DNS hijack
*/

#include <globalVar.h>

bool WALKIE_STATUS = LOW;



void app_main(void){

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    init_spiffs();

//     //Global Inits
    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(gpio_pin_init());
    #ifdef DISPLAY_INCLUDED
         ESP_ERROR_CHECK(display_init());
    #endif   
    ESP_ERROR_CHECK(i2c_init());
    ESP_ERROR_CHECK(bh1750_init());
    ESP_ERROR_CHECK(uart_init());
    // ESP_ERROR_CHECK(init_i2s());
    // ESP_ERROR_CHECK(init_usb_mic());

    xTaskCreate(gpio_run_task, "GPIO TASK", 2048, NULL, 4, &gpio_task_handler);
    xTaskCreate(uart_run_task, "UART TASK", 10000, NULL, 10, &uart_task_handler);
    xTaskCreate(i2c_run_task, "I2C TASK", 5000,NULL, 1, &i2c_task_handler);
    #ifdef DISPLAY_INCLUDED
        xTaskCreate(display_run_task, "DISPLAY TASK", 2048, NULL, 2, &display_task_handler);
    #endif
    start_dns_server();

    // if(battery_init() == ESP_OK){
    //     float v = battery_get_voltage();
    //     float soc = battery_get_soc();
    //     printf("Battery: %.2f V | %.0f%%\n", v, soc);
    // }else{
    //     printf("Could not init bat\n");
    // }

    

    //Last roll out
    #ifdef DISPLAY_INCLUDED
        vTaskDelay(pdMS_TO_TICKS(3000));
        display_target = DISPLAY_EN_OFF;
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(DISPLAY_EN_PIN, LOW);
    #endif
}

