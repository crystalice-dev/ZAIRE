/*
    TITLE: S3-HUB
    DESC: handles ESP_NOW walkie functions; camera; <helmet>BlindSpot Detection; 

*/


#include <globalVar.h>


void app_main(void){
    esp_err_t ret;
    // Initialize NVS -- ALWAYS FIRST
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    //WALKIE
    // ESP_ERROR_CHECK(init_wifi());
    // ESP_ERROR_CHECK(init_esp_now());

    ESP_ERROR_CHECK(uart_init());

    //USB CAMERA
    ESP_ERROR_CHECK(camera_init());
    ESP_ERROR_CHECK(usb_init());

    xTaskCreate(host_run_task, "UART TASK", 10000, NULL, 10, &host_task_handler);
    xTaskCreate(h3_run_task, "H3 TASK", 10000, NULL, 10, &h3_task_handler);

    while (1)
    {
       
    }
    

}
