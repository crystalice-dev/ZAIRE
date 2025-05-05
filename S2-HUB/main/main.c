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

    //Global Inits
    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(gpio_pin_init());
    #ifdef DISPLAY_INCLUDED
        ESP_ERROR_CHECK(display_init());
    #endif   
    // ESP_ERROR_CHECK(init_i2s());
    // ESP_ERROR_CHECK(init_usb_mic());
   xTaskCreate(display_run_task, "DISPLAY TASK", 2048, NULL, 2, &display_task_handler);

   
   start_dns_server();
}

