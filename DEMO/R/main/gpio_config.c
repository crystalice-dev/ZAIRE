#include "globalVar.h"



esp_err_t gpio_init(void){
    esp_err_t err;

    gpio_reset_pin(TOP_BTN);
    gpio_reset_pin(LEFT_BTN);
    gpio_reset_pin(RIGHT_BTN);
    gpio_reset_pin(TOP_LED);
    gpio_reset_pin(LEFT_LED);
    gpio_reset_pin(RIGHT_LED);
    gpio_reset_pin(TEST_LED);

    gpio_config_t top_config = { 
            .pin_bit_mask = (1ULL << TOP_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
        err = gpio_config(&top_config);
        if(err){
            return ESP_FAIL;
        }

    gpio_config_t left_config = {
            .pin_bit_mask = (1ULL << LEFT_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
    err = gpio_config(&left_config);
    if(err){
        return ESP_FAIL;
    }
    gpio_config_t right_config = { 
            .pin_bit_mask = (1ULL << RIGHT_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
    err = gpio_config(&right_config);
    if(err){
        return ESP_FAIL;
    }

    gpio_config_t left_led_config = { 
            .pin_bit_mask = (1ULL << LEFT_LED), // Select GPIO pin
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Disable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
    err = gpio_config(&left_led_config);
    if(err){
        return ESP_FAIL;
    }
    gpio_config_t right_led_config = { 
            .pin_bit_mask = (1ULL << RIGHT_LED), // Select GPIO pin
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Disable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
    err = gpio_config(&right_led_config);
    if(err){
        return ESP_FAIL;
    }   
    gpio_config_t top_led_config = { 
            .pin_bit_mask = (1ULL << TOP_LED), // Select GPIO pin
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Disable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
    err = gpio_config(&top_led_config);
    if(err){
        return ESP_FAIL;
    }

    return ESP_OK;
}