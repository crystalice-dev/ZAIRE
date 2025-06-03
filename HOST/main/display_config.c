#include <globalVar.h>

#ifdef DISPLAY_INCLUDED

#define TAG "OLED_DISPLAY"

u8g2_t display;
bool display_en = LOW;
display_target_t display_target = DISPLAY_MAIN_UI;

esp_err_t display_init(void){
    init_display_gpio();
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.bus.i2c.sda = I2C_1_SDA;
    u8g2_esp32_hal.bus.i2c.scl = I2C_1_SCL;
    u8g2_esp32_hal_init(u8g2_esp32_hal);

    u8g2_Setup_ssd1306_i2c_128x32_univision_f(
        &display, U8G2_R0,
        u8g2_esp32_i2c_byte_cb,
        u8g2_esp32_gpio_and_delay_cb
    );
    
    u8x8_SetI2CAddress(&display.u8x8, 0x3C << 1);  // safer way to write 0x78
    u8g2_InitDisplay(&display);
    u8g2_SetPowerSave(&display, 0);

    
    display_welcome_animation();
    vTaskDelay(pdMS_TO_TICKS(500));
    display_target = DISPLAY_MAIN_UI;
    return ESP_OK;
}

void display_clear(void){
    u8g2_ClearBuffer(&display);
    u8g2_SendBuffer(&display);
}

void display_welcome_animation(void){
    const char *word = "ZAIRE";
    int len = strlen(word);

    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenB18_tr);

    for (int i = 0; i < len; i++) {
        char partial[6] = {0}; // 5 letters + null terminator
        strncpy(partial, word, i + 1);  // Copy first i+1 letters
        u8g2_ClearBuffer(&display);     // Clear previous
        u8g2_DrawStr(&display, 20, 25, partial);  // Draw partial word
        u8g2_SendBuffer(&display);      // Send to display
        vTaskDelay(pdMS_TO_TICKS(5)); //50ms
    }

    vTaskDelay(pdMS_TO_TICKS(200)); //


    // int bar_x = 3;
    // int bar_y = 30;
    // int bar_width = 120;
    // int bar_height = 3;

    // for (int w = 0; w <= bar_width; w += 5) {
    //     u8g2_DrawBox(&display, bar_x, bar_y, w, bar_height);
    //     u8g2_SendBuffer(&display);
    //     vTaskDelay(pdMS_TO_TICKS(0.5));
    // }
}


void display_main_UI(void){
    
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_6x10_tr);

    display_datetime();
    display_location();
    display_elevation();
    u8g2_SetFont(&display, u8g2_font_6x12_tr);
    display_battery(BATTERY_STATUS); // percent

    if (gpio_get_level(CAMERA_ON_PIN) == HIGH) {
        display_camera_icon();
    }

    u8g2_SendBuffer(&display);
}


void init_display_gpio(void){ 
    gpio_config_t camera_on_config = { // Init at 0
        .pin_bit_mask = (1ULL << CAMERA_ON_PIN), // Select GPIO pin
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&camera_on_config);

    gpio_config_t dispaly_btn_config = { // Init at 0
        .pin_bit_mask = (1ULL << DISPLAY_EN_BTN), // Select GPIO pin
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&dispaly_btn_config);

    gpio_config_t display_pin_config = { // 
        .pin_bit_mask = (1ULL << DISPLAY_EN_PIN), // Select GPIO pin
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&display_pin_config);

    display_power_on(); // Start with it on
}

void display_power_on(void){
    gpio_set_level(DISPLAY_EN_PIN, HIGH);
    display_en = HIGH;
}

void display_power_off(void){
    gpio_set_level(DISPLAY_EN_PIN, LOW);
    display_en = LOW;
}

// === UI Elements ===
void display_datetime() {
    const char *time = _get_RTC_time();
    const char *date = _get_RTC_date();
    u8g2_DrawStr(&display, 1, 8, time);
    u8g2_DrawStr(&display, 35, 8, date);
    
}

void display_location(){
    u8g2_DrawStr(&display, 1, 18, gps_latitude);
    u8g2_DrawStr(&display, 1, 28, gps_longitude);
}

void display_elevation(){
    char el[260];
    if(gps_elevation_type == 1){
        snprintf(el, sizeof(el), "%dM", gps_elevation);
    }else{
        snprintf(el, sizeof(el), "%dFT", gps_elevation);
    }
    u8g2_DrawStr(&display, 88, 28, el);
}
    

void display_battery(uint8_t percent) {
    u8g2_DrawFrame(&display, 108, 2, 18, 10);   // Battery body
    u8g2_DrawBox(&display, 126, 4, 2, 6);       // Battery tip

    int fill_width = (percent * 12) / 100;      // 12 is the inner bar max width
    u8g2_DrawBox(&display, 110, 4, fill_width, 6);
}

void display_camera_icon(void){
        // 3. Center: Camera icon (outline)
    // Filled camera body
    u8g2_DrawBox(&display, 80, 4, 20, 12);

    // Lens cutout (simulated by drawing black disc to "punch" through the fill)
    u8g2_SetDrawColor(&display, 0); // 0 = draw black
    u8g2_DrawDisc(&display, 90, 9, 5, U8G2_DRAW_ALL);

    // Restore drawing color to white
    u8g2_SetDrawColor(&display, 1);
    u8g2_DrawCircle(&display, 90, 9, 4, U8G2_DRAW_ALL); // Outline to make lens pop

    // Viewfinder bump
    u8g2_DrawBox(&display, 82, 2, 7, 3);
}

void display_quick_show(void){
    display_target = DISPLAY_MAIN_UI;
    gpio_set_level(DISPLAY_EN_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(7000));
    display_target = DISPLAY_EN_OFF;
    vTaskDelay(pdMS_TO_TICKS(1000));
    gpio_set_level(DISPLAY_EN_PIN, LOW);

}

//FULLSCREEN DISPLAY
void display_low_battery_warning(void){

}

void display_dns_IP(void){

}

#endif
