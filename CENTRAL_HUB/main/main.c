/*
    | Target: ESP32-S3| </br>
    | Envmnt: ESP-IDF 5.5.0 | </br>
    | vrsion: 5.0 | </br>
    | Author: Yann Kabambi | </br>

    # zaire helmets - central hub unit

    (See the README.md file in the upper level 'zaire_helmets' directory for more information about This whole project.)

    The following contains a list of all the responsibilities this firmware has:

    * All camera functions (start/stop dashcam, take picture ie capture).
    * All UART communication [central data process for PI - walkie - (RPi depending on firmware version) ].
    * Blindspot monitoring (trigger led pin to walkie).
    * Connect to other zaire helmet during 'MESH' connection.
    * Check BATTERY LEVEL -- MAX17048G+T10.
    * Check Temp -- AHT20_C2757850.
    * Remote connection && communication.
    * Sends mac addr of helmets in the 'MESH'.
    * Share helmet's walkie mac address for walkie-talkie.

    ### ENJOY - YANN KABAMBI !!
    01-19-2025 07:45🕞
*/

#include "globalVar.h"


int zaire_system_init(){

    // if(nvs_start(WALKIE_NVS_NAMESPACE, &walkie_addr_nvs_registered)){
    //     return ESP_FAIL;
    // }

    // if(gpio_pin_set_up()){ 
    //     return ESP_FAIL;
    // }
    // Start gpio task on success
    // xTaskCreate(gpio_run_task, "gpio_run_task", 2048, NULL, 3, NULL);
    
    if(uart_init()){
        return ESP_FAIL;
    }
    // Start uart task on success
    // xTaskCreate(uart_run_task, "uart_run_task", 5000, NULL, 3, NULL );

    // if(init_i2c()){
    //     return ESP_FAIL;
    // }
    
    // if(bs_monitor_init()){
    //     return ESP_FAIL;
    // }
    // // Start BS task on success

    // check_walkie_addr();

    return ESP_OK;
}


int app_main(void)
{
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
    

     zaire_system_init();

    while (1)
    {
        pi_uart_snd(0x5B);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    

  
    return 0;
}
