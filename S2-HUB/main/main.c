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
//     // ESP_ERROR_CHECK(init_i2s());
//     // ESP_ERROR_CHECK(init_usb_mic());

    xTaskCreate(gpio_run_task, "GPIO TASK", 2048, NULL, 4, &gpio_task_handler);
    xTaskCreate(display_run_task, "DISPLAY TASK", 2048, NULL, 2, &display_task_handler);
    
   
//    start_dns_server();

    printf("%d\n", gpio_get_level(DISPLAY_EN_BTN));

    vTaskDelay(pdMS_TO_TICKS(3000));
    display_target = DISPLAY_EN_OFF;
    vTaskDelay(pdMS_TO_TICKS(2000));
    gpio_set_level(DISPLAY_EN_PIN, LOW);
}

