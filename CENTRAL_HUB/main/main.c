/*
    RESPONSIBILITY:
        * Connect to other compatible devices via classic BT -- HFP_HF
        * Temp Watch
        * BlindStop Monitoring
        * REMOTE -- CONNECTION
        * CONNECT TO TO OTHER HELMETS FOR WALKIE
        * CAMERA
        * 
        // NOTES:
        All the err check uses espressif's ESP_OK or ESP_FAIL returning:
            0 - passed
            1 - failed       
*/

#include "globalVar.h"


nvs_handle_t walkie_addr_nvs_registered;
nvs_handle_t server_nvs_handler;
uint8_t n_value; // place holder for NVS_read();


int init(){

    if(nvs_start(WALKIE_NVS_NAMESPACE, &walkie_addr_nvs_registered)){
        return ESP_FAIL;
    }

    if(gpio_pin_set_up()){ 
        return ESP_FAIL;
    }

    if(uart_init()){
        return ESP_FAIL;
    }

    if(init_i2c()){
        return ESP_FAIL;
    }
    

    if(bs_monitor_init()){
        return ESP_FAIL;
    }

    return ESP_OK;
}

int app_main(void) {
    // Initialize NVS -- ALWAYS FIRST
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    if(ret != ESP_OK){
        vTaskDelay(pdMS_TO_TICKS(500));
        esp_restart();
    }

    if(init()){
        quick_led_flash(4);
        return ESP_FAIL;
    }

    quick_led_flash(2);
    

    return 0;
}
