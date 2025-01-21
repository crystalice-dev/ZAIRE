#include <Arduino.h>
#include "globalVar.h"

TwoWire es8311_i2c(1);


void writeES8311(uint8_t reg, uint8_t value) {
  es8311_i2c.beginTransmission(ES8311_I2C_ADDR);
  es8311_i2c.write(reg);
  es8311_i2c.write(value);
  es8311_i2c.endTransmission();
}

int ES8311_init() {
  
  //ES8311 I2C
  esp_err_t err = es8311_i2c.begin(I2C_1_DATA_PIN, I2C_1_SCL_PIN);
  if(!err){
    return ESP_FAIL;
  }
  writeES8311(0x00, 0x80);  // Reset codec
  delay(10);
  writeES8311(0x00, 0x00);  // Exit reset
  writeES8311(0x01, 0x30);  // Configure power
  writeES8311(0x02, 0x10);  // Configure clock
  // Add additional register settings

  //ES8311 I2S
  i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCK_PIN,
        .ws_io_num = I2S_WS_PIN,
        .data_out_num = I2S_DOUT_PIN,
        .data_in_num = I2S_DIN_PIN
    };

    esp_err_t err0 = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    esp_err_t err1 = i2s_set_pin(I2S_NUM_0, &pin_config);
    esp_err_t err2 = i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

    if(!err0 || !err1 || !err2){
      return ESP_FAIL;
    }

  return ESP_OK;

}
