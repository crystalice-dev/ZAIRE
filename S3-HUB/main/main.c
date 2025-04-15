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

    //USB CAMERA
    ESP_ERROR_CHECK(camera_init());
    ESP_ERROR_CHECK(usb_init());

    printf("%s\n", DEVICE_NAME);

}
