/*
    | Target: ESP32-S3|
    | Envmnt: ESP-IDF 5.5.0 |
    | vrsion: 5.0 |
    | Author: Yann Kabambi |

    zaire helmets - central hub unit
    (See the README.md file in the upper level 'zaire_helmets' directory for more information about This whole project.)

    The following contians a list of all the responsibilities this firmware has:

    All camera functions (start/stop dashcam, take picture ie capture).
    All UART communication [central data process for BM83 - walkie - (RPi depending on firmware version) ].
    Blindspot monitoring (trigger led pin to walkie).
    Connect to other zaire helmet during 'MESH' connection.
    Check BATTERY LEVEL -- MAX17048G+T10.
    Check Temp -- AHT20_C2757850.
    Remote connection && communication.
    Sends mac addr of helmets in the 'MESH'.
    Share helmet's walkie mac address for walkie-talkie.
    ENJOY - YANN KABAMBI !!
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
