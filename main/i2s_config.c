#include <globalVar.h>

bool walkie_speak = false;
bool sendOver = true;
bool recOver = false;
bool speakOut = true; 

int32_t samples_32bit[128];
int16_t samples_16bit[128];
uint8_t samples_8bit[128];
int16_t receive_16bit[128];
int16_t output_16bit[256];

const i2s_port_t REC_I2S_PORT = I2S_NUM_0;
const i2s_port_t SPK_I2S_PORT = I2S_NUM_1;

// rec_i2s_config: Mono 32-bit input from microphone
const i2s_config_t rec_i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_RX,
    .sample_rate = WALKIE_I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = 256,  // Units are in samples
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
};

// spk_i2s_config: Stereo 16-bit output to speaker
const i2s_config_t spk_i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_TX,
    .sample_rate = WALKIE_I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,  // 2-channels (stereo)
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 2,
    .dma_buf_len = 256,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
};

const i2s_pin_config_t rec_pin_config = {
    .bck_io_num = WALKIE_I2S_BCK_MIC,   // BCKL
    .ws_io_num = WALKIE_I2S_WS_MIC,    // LRCL
    .data_out_num = I2S_PIN_NO_CHANGE, // not used (only for speakers)
    .data_in_num = WALKIE_I2S_MIC      // DOUT
};
const i2s_pin_config_t spk_pin_config = {
    .bck_io_num = WALKIE_I2S_BCK_SPK,
    .ws_io_num = WALKIE_I2S_WS_SPK,
    .data_out_num = WALKIE_I2S_SPK,
    .data_in_num = I2S_PIN_NO_CHANGE   // Not used
};  

esp_err_t i2s_init(void){

    esp_err_t err;
    err = i2s_driver_install(REC_I2S_PORT, &rec_i2s_config, 0, NULL);
    if (err != ESP_OK) return ESP_FAIL;

    err = i2s_set_pin(REC_I2S_PORT, &rec_pin_config);
    if (err != ESP_OK) return ESP_FAIL;

    err = i2s_driver_install(SPK_I2S_PORT, &spk_i2s_config, 0, NULL);
    if (err != ESP_OK) return ESP_FAIL;

    err = i2s_set_pin(SPK_I2S_PORT, &spk_pin_config);
    if (err != ESP_OK) return ESP_FAIL;

    return ZAIRE_OK;
}

// Read samples from I2S microphone: Convert 32-bit to 16-bit with clamping
int I2Sread(int16_t *samples, int count){
    size_t bytes_read = 0;
    if (count > 128) {
        count = 128;  // Limit to buffer size
    }
    i2s_read(REC_I2S_PORT, (char *)samples_32bit, sizeof(int32_t) * count, &bytes_read, portMAX_DELAY);
    int samples_read = bytes_read / sizeof(int32_t);
    for (int i = 0; i < samples_read; i++) {
        int32_t temp = samples_32bit[i] >> 11;
        samples[i] = (temp > INT16_MAX) ? INT16_MAX : (temp < -INT16_MAX) ? -INT16_MAX : (int16_t)temp;
    }
    return samples_read;
}

// Write samples to I2S speaker
void I2Swrite(int16_t *samples, int count) {
    size_t bytes_written;
    i2s_write(SPK_I2S_PORT, samples, sizeof(int16_t) * count, &bytes_written, portMAX_DELAY); 
}

// Convert 16-bit signed samples to 8-bit unsigned for transmission
void covert_bit(int16_t *temp_samples_16bit, uint8_t *temp_samples_8bit, uint8_t len) {
  for (uint8_t i = 0; i < len; i++) {
    temp_samples_8bit[i] = (temp_samples_16bit[i] + 32768) >> 8;
  }
}