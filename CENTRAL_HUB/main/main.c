/*
    | Target: ESP32-S3| </br>
    | Envmnt: ESP-IDF 5.5.0 | </br>
    | vrsion: 5.0 | </br>
    | Author: Yann Kabambi | </br>

    # zaire helmets - central hub unit

    (See the README.md file in the upper level 'zaire_helmets' directory for more information about This whole project.)

    The following contains a list of all the responsibilities this firmware has:

    * All camera functions (start/stop dashcam, take picture ie capture).
    * All UART communication [central data process for BM83 - walkie - (RPi depending on firmware version) ].
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


nvs_handle_t walkie_addr_nvs_registered;
nvs_handle_t server_nvs_handler;
uint8_t n_value; // place holder for NVS_read();
bool first_boot = 1;


int check_walkie_addr(){
    uint8_t isAddr_in = nvs_read(walkie_addr_nvs_registered, WALKIE_ADDR_KEY);

    if(isAddr_in){
        printf("got it\n");
        size_t temp = sizeof(walkie_address); // Ensure temp has the correct size of the buffer
        esp_err_t err = nvs_get_blob(walkie_addr_nvs_registered, WALKIE_NVS_NAMESPACE, walkie_address, &temp); // Pass the address of temp
        if(err == ESP_OK){
            walkie_interject_number = 6; // Ensure walkie mac addr never changes
            for(int i = 0; i < 6; i++){
                printf("0x%02X", walkie_address[i]);
                if(i < 5){
                    printf(":");
                }
            }
            printf("\n");
        }
    }else{
        vTaskDelay(pdMS_TO_TICKS(1000));
        walkie_get_addr_port = 1;
        walkie_interject_number = 0;
        walkie_uart_snd(GET_WALKIE_ADDR);
        while (walkie_interject_number < 6 && walkie_get_addr_port == 1){
            vTaskDelay(pdMS_TO_TICKS(50)); // wait for Walkie to return walkie mac
        }
    }

    return 0;
}

int zaire_system_init(){

    if(nvs_start(WALKIE_NVS_NAMESPACE, &walkie_addr_nvs_registered)){
        return ESP_FAIL;
    }

    if(gpio_pin_set_up()){ 
        return ESP_FAIL;
    }
    // Start gpio task on success
    xTaskCreate(gpio_run_task, "gpio_run_task", 2048, NULL, 3, NULL);
    
    if(uart_init()){
        return ESP_FAIL;
    }
    // Start uart task on success
    xTaskCreate(uart_run_task, "uart_run_task", 5000, NULL, 3, NULL );

    if(init_i2c()){
        return ESP_FAIL;
    }
    
    if(bs_monitor_init()){
        return ESP_FAIL;
    }
    // Start BS task on success

    check_walkie_addr();

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

    if(zaire_system_init()){
        quick_led_flash(4);
        return ESP_FAIL;
    }

   
    quick_led_flash(2);
   
    return 0;
}
