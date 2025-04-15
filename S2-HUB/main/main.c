/*
    TITLE: S2-HUB
    DESC: handles ESP_NOW non-walkie functions

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

    //USB MIC
    ESP_ERROR_CHECK(init_i2s());
    ESP_ERROR_CHECK(init_usb_mic());

    printf("%s\n", DEVICE_NAME);

}
