#include <globalVar.h>



esp_err_t gpio_pin_init(void){
    esp_err_t err;

    #ifdef DISPLAY_INCLUDED
        gpio_config_t camera_on_config = { // Init at 0
            .pin_bit_mask = (1ULL << CAMERA_ON_PIN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
        err = gpio_config(&camera_on_config);
        if(err){
            return ESP_FAIL;
        }
    #endif
    
    return ESP_OK;
}