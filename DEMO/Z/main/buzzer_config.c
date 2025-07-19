#include "globalVar.h"



void buzzer_init()
{
    ledc_timer_config_t timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .freq_hz          = BUZZER_FREQ_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    ledc_channel_config_t channel = {
        .gpio_num       = BUZZER,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = BUZZER_LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0,
        .hpoint         = 0,
        .flags.output_invert = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&channel));
}

void buzzer_on(){
    ledc_set_freq(LEDC_LOW_SPEED_MODE, LEDC_TIMER_0, 7500);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, BUZZER_LEDC_CHANNEL, BUZZER_DUTY);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, BUZZER_LEDC_CHANNEL);
}

void buzzer_off(){
    ledc_set_duty(LEDC_LOW_SPEED_MODE, BUZZER_LEDC_CHANNEL, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, BUZZER_LEDC_CHANNEL);
}

void quick_buzz(){
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(75));
    buzzer_off();
}

void double_quick_buzz(){
    quick_buzz();
    vTaskDelay(pdMS_TO_TICKS(50));
    quick_buzz();
}