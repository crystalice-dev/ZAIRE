#include <globalVar.h>


typedef struct {
    camera_fb_t *cam_fb_p;
    uvc_fb_t uvc_fb;
} fb_t;
fb_t s_fb;

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

uvc_fb_t* camera_fb_get_cb(void *cb_ctx){
    (void)cb_ctx;
    vTaskDelay(pdMS_TO_TICKS(10));
    s_fb.cam_fb_p = esp_camera_fb_get();
    if (!s_fb.cam_fb_p) {
        return NULL;
    }
    s_fb.uvc_fb.buf = s_fb.cam_fb_p->buf;
    s_fb.uvc_fb.len = s_fb.cam_fb_p->len;
    s_fb.uvc_fb.width = s_fb.cam_fb_p->width;
    s_fb.uvc_fb.height = s_fb.cam_fb_p->height;
    s_fb.uvc_fb.format = s_fb.cam_fb_p->format;
    s_fb.uvc_fb.timestamp = s_fb.cam_fb_p->timestamp;

    if (s_fb.uvc_fb.len > UVC_MAX_FRAMESIZE_SIZE) {
        ESP_LOGE("CAMERA", "Frame size %d is larger than max frame size %d", s_fb.uvc_fb.len, UVC_MAX_FRAMESIZE_SIZE);
        esp_camera_fb_return(s_fb.cam_fb_p);
        return NULL;
    }
    return &s_fb.uvc_fb;

}

static void camera_fb_return_cb(uvc_fb_t *fb, void *cb_ctx){
    (void)cb_ctx;
    assert(fb == &s_fb.uvc_fb);
    esp_camera_fb_return(s_fb.cam_fb_p);
}

static void camera_stop_cb(void *cb_ctx){
    (void)cb_ctx;
    
}

static esp_err_t camera_start_cb(uvc_format_t format, int width, int height, int rate, void *cb_ctx){
    return ZAIRE_OK;
}

esp_err_t usb_init(void){

    uint8_t *uvc_buffer = (uint8_t *)malloc(UVC_MAX_FRAMESIZE_SIZE);
    uvc_device_config_t config = {
        .uvc_buffer = uvc_buffer,
        .uvc_buffer_size = UVC_MAX_FRAMESIZE_SIZE,
        .start_cb = camera_start_cb,
        .fb_get_cb = camera_fb_get_cb,
        .fb_return_cb = camera_fb_return_cb,
        .stop_cb = camera_stop_cb,
    };

    esp_err_t ret = uvc_device_config(0, &config);
    if(ret != ESP_OK){
        ESP_LOGE("USB", "Could not config device %s", esp_err_to_name(ret));
        return ESP_FAIL;
    }
    ret = uvc_device_init();
    if(ret != ESP_OK){
        ESP_LOGE("USB", "Could not init device %s", esp_err_to_name(ret));
        return ESP_FAIL;
    }

    return ESP_OK;
}