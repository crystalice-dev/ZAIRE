#include <globalVar.h>

#define TAG "OLED_DISPLAY"

u8g2_t display;

esp_err_t display_init(void){
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.bus.i2c.sda = I2C_0_SDA;
    u8g2_esp32_hal.bus.i2c.scl = I2C_0_SCL;
    u8g2_esp32_hal_init(u8g2_esp32_hal);


    u8g2_Setup_ssd1306_i2c_128x32_univision_f(
        &display, U8G2_R0,
        u8g2_esp32_i2c_byte_cb,
        u8g2_esp32_gpio_and_delay_cb
    );
    u8x8_SetI2CAddress(&display.u8x8, 0x3C << 1);  // safer way to write 0x78
   
    u8g2_InitDisplay(&display);
    u8g2_SetPowerSave(&display, 0);

    return ESP_OK;
}

