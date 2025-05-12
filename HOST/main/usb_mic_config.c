#include <globalVar.h>

const char* TAG = "MIC";


const i2s_config_t i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_RX,
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, //Tie LR to GND
    .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 256,
    .use_apll = false // change to true if mic requires it
};

const i2s_pin_config_t i2s_pin_config = {
    .bck_io_num = I2S_CLK,   // BCKL
    .ws_io_num = I2S_WS,    // LRCL
    .data_out_num = -1, // not used (only for speakers)
    .data_in_num = I2S_DIN  //
};

esp_err_t init_i2s(void){
    esp_err_t err0, err1;
    err0 = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    err1 = i2s_set_pin(I2S_PORT, &i2s_pin_config);

    if(err0 != ESP_OK || err1 != ESP_OK){
        return ESP_FAIL;
    }

    return ESP_OK;
}


esp_err_t init_usb_mic(void){

    uac_device_config_t config = {
        .output_cb = NULL,
        .input_cb = uac_device_input_cb,
        .set_mute_cb = NULL,
        .set_volume_cb = NULL,
        .cb_ctx = NULL,
    };

    if(uac_device_init(&config) != ESP_OK){
        return ESP_FAIL;
    }


    return ESP_OK;

}

int uac_device_input_cb(uint8_t *buf, size_t len, size_t *bytes_read, void *arg) {

    size_t frames = len / 2; // Number of 16-bit samples requested

    int32_t *raw_samples = malloc(frames * sizeof(int32_t));
    int16_t *out_samples = malloc(frames * sizeof(int16_t));
    if (!raw_samples || !out_samples) {
        ESP_LOGE("UAC", "Failed to allocate audio buffers");
        *bytes_read = 0;
        return ESP_FAIL;
    }

    size_t bytes_in = 0;
    esp_err_t err = i2s_read(I2S_PORT, raw_samples, frames * sizeof(int32_t), &bytes_in, portMAX_DELAY);
    if (err != ESP_OK || bytes_in == 0) {
        ESP_LOGE("UAC", "I2S read failed");
        free(raw_samples);
        free(out_samples);
        *bytes_read = 0;
        return ESP_FAIL;
    }

    size_t actual_frames = bytes_in / sizeof(int32_t);

   
    float gain = 0.05;

    for (int i = 0; i < actual_frames; i++) {
        int32_t sample = raw_samples[i] >> 8; // Convert 24-bit to 16-bit MSB
        sample = (int32_t)(sample * gain);    // Apply gain

        // Clip to 16-bit signed range to avoid overflow
        if (sample > INT16_MAX) sample = INT16_MAX;
        if (sample < INT16_MIN) sample = INT16_MIN;

        out_samples[i] = (int16_t)sample;
    }

    memcpy(buf, out_samples, actual_frames * sizeof(int16_t));
    *bytes_read = actual_frames * sizeof(int16_t);

    free(raw_samples);
    free(out_samples);
    return ESP_OK;
}
