#include "globalVar.h"

int gpio_pin_set_up(void){
    gpio_config_t purpose_btn_l_conf = { // Init at 0
        .pin_bit_mask = (1ULL << PURPOSE_BTN_L), // Select GPIO pin
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t btn_l =  gpio_config(&purpose_btn_l_conf);

    gpio_config_t purpose_btn_r_conf = { // Init at 0
        .pin_bit_mask = (1ULL << PURPOSE_BTN_R), // Select GPIO pin
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t btn_r = gpio_config(&purpose_btn_r_conf);
    
    gpio_config_t walkie_pin_conf = { // Init at 0
        .pin_bit_mask = (1ULL << WALKIE_PIN), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t walkie_pin = gpio_config(&walkie_pin_conf);

    gpio_config_t purpose_led_pin_conf = { // Init at 0
        .pin_bit_mask = (1ULL << PURPOSE_LED), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t led_pin = gpio_config(&purpose_led_pin_conf);

    gpio_config_t bs_lt_led_conf = { // Init at 0
        .pin_bit_mask = (1ULL << BS_LT_LED_PIN), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t bs_l = gpio_config(&bs_lt_led_conf);

    gpio_config_t bs_rt_led_conf = { // Init at 0
        .pin_bit_mask = (1ULL << BS_RT_LED_PIN), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t bs_r = gpio_config(&bs_rt_led_conf);

    gpio_config_t emerg_pin_conf = { // Init at 0
        .pin_bit_mask = (1ULL << EMERG_PIN), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t emerg_pin_r = gpio_config(&emerg_pin_conf);

    //Buzzer


    if(btn_l == ESP_OK && btn_r == ESP_OK && walkie_pin == ESP_OK && led_pin == ESP_OK && bs_l == ESP_OK && bs_r == ESP_OK && emerg_pin_r == ESP_OK){
            
            return ESP_OK;
    }
    return ESP_FAIL;
}  

void quick_led_flash(uint8_t n){
    
    for(int i = 0; i < n; i++){
        gpio_set_level(PURPOSE_LED, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_set_level(PURPOSE_LED, 0);
        vTaskDelay(pdMS_TO_TICKS(100));
    }

}

void buzz(void){
    // ESP_ERROR_CHECK(ledc_set_duty(buzzer_c_channel.speed_mode, buzzer_c_channel.channel, 4096)); // 50% duty cycle
    // ESP_ERROR_CHECK(ledc_update_duty(buzzer_c_channel.speed_mode, buzzer_c_channel.channel));

    // // Wait for duration seconds
    // vTaskDelay(pdMS_TO_TICKS(duration));

    // // Stop the buzzer
    // ESP_ERROR_CHECK(ledc_set_duty(buzzer_c_channel.speed_mode, buzzer_c_channel.channel, 0));
    // ESP_ERROR_CHECK(ledc_update_duty(buzzer_c_channel.speed_mode, buzzer_c_channel.channel));
}

