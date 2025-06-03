#include <globalVar.h>

#ifdef LIGHTS_INCLUDED

led_target_mode_t led_target_mode[2] = {LED_OFF, LED_OFF};
led_target_stage_t led_target_stage = NORMAL;

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


void led_welcome_animation(led_strip_handle_t led_strip){

    const int total_leds = LED_STRIP_LED_NUMBERS;
    const int center = total_leds / 2; // works with even or odd

    gpio_config_t front_white_led_config = { // Init at 0
        .pin_bit_mask = (1ULL << FRONT_WHITE_LED), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&front_white_led_config);
    led_front_white_on();

    // First: Outward from center to both ends
    for (int offset = 0; offset < center; offset++) {
        int left = center - offset - 1;
        int right = center + offset;

        if (left >= 0) {
            led_strip_set_pixel(led_strip, left, AMBER_R, AMBER_G, AMBER_B);
        }
        if (right < total_leds) {
            led_strip_set_pixel(led_strip, right, AMBER_R, AMBER_G, AMBER_B);
        }

        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    // Hold full for a moment
    vTaskDelay(pdMS_TO_TICKS(300));

    // Then: Collapse back inward to center
    for (int offset = center - 1; offset >= 0; offset--) {
        int left = center - offset - 1;
        int right = center + offset;

        if (left >= 0) {
            led_strip_set_pixel(led_strip, left, 0, 0, 0);
        }
        if (right < total_leds) {
            led_strip_set_pixel(led_strip, right, 0, 0, 0);
        }

        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    led_brake_red(led_strip);
    // Final pause
    led_target_mode[0] = LED_OFF;
    led_target_mode[1] = LED_OFF;
}

void led_front_white_on(void){
    gpio_set_level(FRONT_WHITE_LED, LOW);
}

void led_front_white_off(void){
    gpio_set_level(FRONT_WHITE_LED, HIGH);

}

void led_right_turn(led_strip_handle_t led_strip){

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

void led_left_turn(led_strip_handle_t led_strip){
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

void led_brake_red(led_strip_handle_t led_strip){
    for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
        led_strip_set_pixel(led_strip, i, 255, 0, 0); // Red
    }
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(2000));

    for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
        led_strip_set_pixel(led_strip, i, 0, 0, 0);
    }
    led_strip_refresh(led_strip);
}

void led_pairing_master_search_blue(led_strip_handle_t led_strip){

    const int total_leds = LED_STRIP_LED_NUMBERS;
    const int center = total_leds / 2; // works with even or odd

    gpio_config_t front_white_led_config = { // Init at 0
        .pin_bit_mask = (1ULL << FRONT_WHITE_LED), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&front_white_led_config);

    // First: Outward from center to both ends
    for (int offset = 0; offset < center; offset++) {
        int left = center - offset - 1;
        int right = center + offset;

        if (left >= 0) {
            led_strip_set_pixel(led_strip, left, 0, 0, 255); // BLUE
        }
        if (right < total_leds) {
            led_strip_set_pixel(led_strip, right, 0, 0, 255); // BLUE
        }

        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    // Hold full for a moment
    vTaskDelay(pdMS_TO_TICKS(300));

    // Then: Collapse back inward to center
    for (int offset = center - 1; offset >= 0; offset--) {
        int left = center - offset - 1;
        int right = center + offset;

        if (left >= 0) {
            led_strip_set_pixel(led_strip, left, 0, 0, 0); // OFF
        }
        if (right < total_leds) {
            led_strip_set_pixel(led_strip, right, 0, 0, 0); // OFF
        }

        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void led_pairing_sync_blue(led_strip_handle_t led_strip) {
    const int total_leds = LED_STRIP_LED_NUMBERS;
    const int dim_steps = 10;
    const int max_brightness = 255;

    // Gradually brighten all LEDs up
    for (int step = 1; step <= dim_steps; step++) {
        int brightness = max_brightness * step / dim_steps;

        for (int i = 0; i < total_leds; i++) {
            led_strip_set_pixel(led_strip, i, 0, 0, brightness);
        }

        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelay(pdMS_TO_TICKS(300)); // Hold full brightness for a moment

    // Gradually dim all LEDs back down
    for (int step = 1; step <= dim_steps; step++) {
        int brightness = max_brightness * (dim_steps - step) / dim_steps;

        for (int i = 0; i < total_leds; i++) {
            led_strip_set_pixel(led_strip, i, 0, 0, brightness);
        }

        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}



void led_pairing_slave_search_blue(led_strip_handle_t led_strip) {
    const int total_leds = LED_STRIP_LED_NUMBERS;
    const int blue_brightness = 255; // Full blue

    for (int i = 0; i < total_leds; i++) {
        led_strip_set_pixel(led_strip, i, 0, 0, blue_brightness);
    }

    led_strip_refresh(led_strip);
}


void led_pairing_complete(led_strip_handle_t led_strip){
    for(int i = 0; i < 2; i++){
        led_pairing_slave_search_blue(led_strip);
        vTaskDelay(pdMS_TO_TICKS(250));
        led_off_all(led_strip);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}

void led_off_all(led_strip_handle_t led_strip){

    for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
        led_strip_set_pixel(led_strip, i, 0, 0, 0);
    }
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(250));

}

#endif