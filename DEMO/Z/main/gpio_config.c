#include <globalVar.h>



esp_err_t gpio_pin_init(void){
    esp_err_t err;

    gpio_config_t purpose_config = { // Init at 0
            .pin_bit_mask = (1ULL << PURPOSE_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
        err = gpio_config(&purpose_config);
        if(err){
            return ESP_FAIL;
        }

    gpio_config_t walkie_config = { // Init at 0
            .pin_bit_mask = (1ULL << WALKIE_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
        err = gpio_config(&walkie_config);
        if(err){
            return ESP_FAIL;
        }
    
    return ESP_OK;
}