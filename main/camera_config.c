#include <globlaVar.h>
#ifdef CAMERA_INCLUDED





esp_err_t init_camera(){

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
        config.frame_size = FRAMESIZE_96X96; //FRAMESIZE_UXGA;             
        config.pixel_format = PIXFORMAT_JPEG;           // MJPEG for UVC
        config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
        config.fb_location = CAMERA_FB_IN_DRAM; //CAMERA_FB_IN_PSRAM;
        config.jpeg_quality = 2;
        config.fb_count = 2;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        printf("failed\n");
        return ESP_FAIL;
    }
    // initial sensors are flipped vertically and colors are a bit saturated
    sensor_t *s = esp_camera_sensor_get();

     switch (s->id.PID) {
        case OV2640_PID:
            s->set_vflip(s, 1);
            printf("Detected OV2640 - vertical flip applied\n");
            break;
        case OV5640_PID:
            s->set_vflip(s, 0);  // OV5640 is usually correct orientation
            printf("Detected OV5640 - no flip applied.\n");
            break;
        default:
            break;
    }

    // 🔧 Apply tuning for OV5640 to avoid black frames
    s->set_gain_ctrl(s, 1);        // Enable auto gain
    s->set_exposure_ctrl(s, 1);    // Enable auto exposure
    //s->set_awb(s, 1);              // Enable auto white balance

    s->set_brightness(s, 1);       // Brighten image (range -2 to 2)
    s->set_saturation(s, 1);  

    return ESP_OK;
}

#endif