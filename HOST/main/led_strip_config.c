#include <globalVar.h>



led_strip_handle_t configure_led_stip(void){
    led_strip_config_t strip_config = {
        .strip_gpio_num = BACK_LED,
        .max_leds = LED_STRIP_LED_NUMBERS,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB,
        .led_model = LED_MODEL_SK6812,
        .flags.invert_out = false,
    };

    led_strip_rmt_config_t rmt_config = {
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
        .rmt_channel = 0,
#else
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = LED_STRIP_RMT_RES_HZ,
        .flags.with_dma = false,
#endif
    };

    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    return led_strip;
}

void play_right_turn(led_strip_handle_t led_strip){

    const int start_led = 5;  // LED 6
    const int end_led = 9;    // LED 10

    for (int i = start_led; i <= end_led; i++) {
        led_strip_set_pixel(led_strip, i, AMBER_R, AMBER_G, AMBER_B);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelay(pdMS_TO_TICKS(200));

    for (int i = start_led; i <= end_led; i++) {
        led_strip_set_pixel(led_strip, i, 0, 0, 0);
    }
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(200));

}

void play_left_turn(led_strip_handle_t led_strip){
    const int start_led = 4;  // LED 5 (index 4)
    const int end_led = 0;    // LED 1 (index 0)

    for (int i = start_led; i >= end_led; i--) {
        led_strip_set_pixel(led_strip, i, AMBER_R, AMBER_G, AMBER_B);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelay(pdMS_TO_TICKS(200));

    for (int i = start_led; i >= end_led; i--) {
        led_strip_set_pixel(led_strip, i, 0, 0, 0);
    }
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void play_brake_red(led_strip_handle_t led_strip){
    for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
        led_strip_set_pixel(led_strip, i, 255, 0, 0); // Red
    }
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(3000));

    for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
        led_strip_set_pixel(led_strip, i, 0, 0, 0);
    }
    led_strip_refresh(led_strip);
}

void turn_off_all(led_strip_handle_t led_strip){

    for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
        led_strip_set_pixel(led_strip, i, 0, 0, 0);
    }
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(250));

}
