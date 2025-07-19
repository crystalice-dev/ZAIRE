#include "globalVar.h"

#ifdef BLINDSPOT_INCLUDED

int32_t  bs_rt_distance;
int32_t  bs_lt_distance;

void bs_monitor_init(){

    gpio_config_t right_conf = {
        .pin_bit_mask = (1ULL << BS_TRIG_RIGHT),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = 0,
        .pull_up_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&right_conf);

    right_conf.pin_bit_mask = (1ULL << BS_ECHO_RIGHT);
    right_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&right_conf);

    gpio_config_t left_conf = {
        .pin_bit_mask = (1ULL << BS_TRIG_LEFT),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = 0,
        .pull_up_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&left_conf);

    left_conf.pin_bit_mask = (1ULL << BS_ECHO_LEFT);
    left_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&left_conf);


    // Right LED
    ledc_channel_config_t ledc_channel_right = {
        .channel    = LEDC_CHANNEL_1,
        .duty       = 0,
        .gpio_num   = BS_LED_RIGHT,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel_right);

    // Left LED
    ledc_channel_config_t ledc_channel_left = {
        .channel    = LEDC_CHANNEL_2,
        .duty       = 0,
        .gpio_num   = BS_LED_LEFT,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel_left);

}

int32_t bs_rt_get_distance(void){
    int64_t start_time, end_time;
    int32_t duration_us;

    // Send a 10µs trigger pulse
    gpio_set_level(BS_TRIG_RIGHT, 0);
    vTaskDelay(pdMS_TO_TICKS(2));
    gpio_set_level(BS_TRIG_RIGHT, 1);
    vTaskDelay(pdMS_TO_TICKS(2));  // ~20µs
    gpio_set_level(BS_TRIG_RIGHT, 0);

    // Wait for ECHO to go HIGH
    start_time = esp_timer_get_time();
    while (gpio_get_level(BS_ECHO_RIGHT) == 0) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // timeout waiting for HIGH
        }
    }

    // Measure ECHO HIGH duration
    start_time = esp_timer_get_time();
    while (gpio_get_level(BS_ECHO_RIGHT) == 1) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // timeout waiting for LOW
        }
    }
    end_time = esp_timer_get_time();

    duration_us = end_time - start_time;

    // Convert to centimeters (343 m/s → ~29.1 µs/cm round-trip → /58)
    int32_t distance_cm = duration_us / 58;

    return distance_cm;

}

int32_t bs_lt_get_distance(void){
    int64_t start_time, end_time;
    int32_t duration_us;

    // Send a 10µs trigger pulse
    gpio_set_level(BS_TRIG_LEFT, 0);
    vTaskDelay(pdMS_TO_TICKS(2));
    gpio_set_level(BS_TRIG_LEFT, 1);
    vTaskDelay(pdMS_TO_TICKS(2));  // ~20µs
    gpio_set_level(BS_TRIG_LEFT, 0);

    // Wait for ECHO to go HIGH
    start_time = esp_timer_get_time();
    while (gpio_get_level(BS_ECHO_LEFT) == 0) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // timeout waiting for HIGH
        }
    }

    // Measure ECHO HIGH duration
    start_time = esp_timer_get_time();
    while (gpio_get_level(BS_ECHO_LEFT) == 1) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // timeout waiting for LOW
        }
    }
    end_time = esp_timer_get_time();

    duration_us = end_time - start_time;

    // Convert to centimeters (343 m/s → ~29.1 µs/cm round-trip → /58)
    int32_t distance_cm = duration_us / 58;

    return distance_cm;
}

void set_BS_led_right(uint8_t duty) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
}

void set_BS_led_left(uint8_t duty) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);
}

void set_BS_led_brightness(uint8_t duty_right, uint8_t duty_left) {
    set_BS_led_right(duty_right);
    set_BS_led_left(duty_left);
}

#endif