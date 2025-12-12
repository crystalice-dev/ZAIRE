#include <globalVar.h>


esp_err_t camera_init(void){

    camera_config_t config;
        config.ledc_channel = LEDC_CHANNEL_0;
        config.ledc_timer = LEDC_TIMER_0;
        config.pin_d0 = Y2_GPIO_NUM;
        config.pin_d1 = Y3_GPIO_NUM;
        config.pin_d2 = Y4_GPIO_NUM;
        config.pin_d3 = Y5_GPIO_NUM;
        config.pin_d4 = Y6_GPIO_NUM;
        config.pin_d5 = Y7_GPIO_NUM;
        config.pin_d6 = Y8_GPIO_NUM;
        config.pin_d7 = Y9_GPIO_NUM;
        config.pin_xclk = XCLK_GPIO_NUM;
        config.pin_pclk = PCLK_GPIO_NUM;
        config.pin_vsync = VSYNC_GPIO_NUM;
        config.pin_href = HREF_GPIO_NUM;
        config.pin_sccb_sda = SIOD_GPIO_NUM;
        config.pin_sccb_scl = SIOC_GPIO_NUM;
        config.pin_pwdn = PWDN_GPIO_NUM;
        config.pin_reset = RESET_GPIO_NUM;
        config.xclk_freq_hz = 20000000;
        config.frame_size = FRAMESIZE_SVGA;             // 800x600
        config.pixel_format = PIXFORMAT_JPEG;           // MJPEG for UVC
        config.grab_mode = CAMERA_GRAB_LATEST;
        config.fb_location = CAMERA_FB_IN_PSRAM;
        config.jpeg_quality = 7;                       // Quality 0-63 lower means higher quality
        config.fb_count = 2;
    

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ESP_LOGE("CAMERA", "ERROR: COULD NOT INIT CAMERA -- %s", esp_err_to_name(err));
        return ESP_FAIL;
    }
    // initial sensors are flipped vertically and colors are a bit saturated
    sensor_t *s = esp_camera_sensor_get();

    switch (s->id.PID) {
        case OV2640_PID:
            s->set_vflip(s, 1);
            break;
        case OV5640_PID:
            s->set_vflip(s, 0);  // OV5640 is usually correct orientation
            break;
        default:
            ESP_LOGW("CAMERA", "Unknown sensor PID: 0x%04x", s->id.PID);
            break;
    }



    // 🔧 Apply tuning for OV5640 to avoid black frames*
    s->set_gain_ctrl(s, 1);        // Enable auto gain
    s->set_exposure_ctrl(s, 1);    // Enable auto exposure
    //s->set_awb(s, 1);              // Enable auto white balance

    s->set_brightness(s, 1);       // Brighten image (range -2 to 2)
    s->set_saturation(s, 1);       // Boost color (range -2 to 2)

    // Optional: manually tweak exposure if needed
    // s->set_aec_value(s, 800);   // Manual exposure value

    return ESP_OK;

}

int count  = 0;
char buffer[128];
void camera_take_picture(void){
    //Get a frame buffer from the camera
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        return;
    }

    //JPG based on config
    if (fb->format != PIXFORMAT_JPEG) {

        //could convert here if needed, but for now just return it.
        esp_camera_fb_return(fb);
        return;
    }

    sniprintf(buffer, sizeof(buffer), "/spiffs/media/photos/photo_%d.jpg", count++);

    const char *file_path = buffer;

    // Open file on SPIFFS
    FILE *f = fopen(file_path, "wb");
    if (!f) {

        esp_camera_fb_return(fb);
        return;
    }

    // Write the JPEG data to file
    size_t written = fwrite(fb->buf, 1, fb->len, f);
    fclose(f);                 // close file
    esp_camera_fb_return(fb);  // return frame buffer to driver

    if (written != fb->len) {

        return;
    }

}
