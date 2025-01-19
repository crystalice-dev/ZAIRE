#include "globalVar.h"

int32_t  bs_rt_distance;
int32_t  bs_lt_distance;

int bs_monitor_init(){
    esp_err_t err_r_t;
    esp_err_t err_l_t;
    esp_err_t err_r_e;
    esp_err_t err_l_e;

    gpio_config_t io_rt_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << BS_RT_TRIG_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    err_r_t = gpio_config(&io_rt_conf);

    io_rt_conf.mode = GPIO_MODE_INPUT;
    io_rt_conf.pin_bit_mask = (1ULL << BS_RT_ECHO_PIN);
    err_r_e = gpio_config(&io_rt_conf);

    gpio_config_t io_lt_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << BS_LT_TRIG_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    err_l_t = gpio_config(&io_lt_conf);

    io_lt_conf.mode = GPIO_MODE_INPUT;
    io_lt_conf.pin_bit_mask = (1ULL << BS_LT_ECHO_PIN);
    err_l_e = gpio_config(&io_lt_conf);

    if(err_r_t == ESP_FAIL || err_r_e == ESP_FAIL || err_l_t == ESP_FAIL || err_l_e == ESP_FAIL){
        return ESP_FAIL;
    }

    return ESP_OK;

}

int32_t bs_rt_get_distance(void){
    int64_t start_time, end_time;
    int32_t duration_us;

    // Send a 10us trigger pulse
    gpio_set_level(BS_RT_TRIG_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(2));
    gpio_set_level(BS_RT_TRIG_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(BS_RT_TRIG_PIN, 0);

    // Wait for echo to go HIGH
    start_time = esp_timer_get_time();
    while (gpio_get_level(BS_RT_ECHO_PIN) == 0) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // Return -1 if timeout occurs
        }
    }

    // Measure the time echo stays HIGH
    start_time = esp_timer_get_time();
    while (gpio_get_level(BS_RT_ECHO_PIN) == 1) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // Return -1 if timeout occurs
        }
    }
    end_time = esp_timer_get_time();

    // Calculate duration in microseconds
    duration_us = end_time - start_time;

    // Calculate distance in feet (duration_us -> cm -> ft)
    // Speed of sound: 343 m/s, ~29.1 µs/cm round-trip
    return ( duration_us / 58.0 )* 0.0328084; // Return the distance in feet

}

uint8_t bs_lt_get_distance(void){
    int64_t start_time, end_time;
    int32_t duration_us;

    // Send a 10us trigger pulse
        gpio_set_level(BS_LT_TRIG_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(4));
        gpio_set_level(BS_LT_TRIG_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(20));
        gpio_set_level(BS_LT_TRIG_PIN, 0);

        // Wait for echo to go HIGH
        start_time = esp_timer_get_time();
        while (gpio_get_level(BS_LT_ECHO_PIN) == 0) {
            if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
                return -1;
            }
        }

        // Measure the time echo stays HIGH
        start_time = esp_timer_get_time();
        while (gpio_get_level(BS_LT_ECHO_PIN) == 1) {
            if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
                return -1;
            }
        }
        end_time = esp_timer_get_time();

        // Calculate duration in microseconds
        duration_us = end_time - start_time;

        // Calculate distance in cm (speed of sound: 343 m/s => 29.1 us/cm round-trip)
        return (duration_us / 58) / 30.48;
    
}

bool x = 0;void bs_right_monitor_task(void *vpParam){

    while (1)
    {
        bs_rt_distance = bs_rt_get_distance();
        
        if(bs_rt_distance > 0){
            printf("%li\n", bs_rt_distance);
        }
        vTaskDelay(pdMS_TO_TICKS(50)); //prevent timeout
        
    }
    

}

void bs_left_monitor_task(void *vpParam){

    while (1)
    {
        gpio_set_level(BS_LT_LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(BS_LT_LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}