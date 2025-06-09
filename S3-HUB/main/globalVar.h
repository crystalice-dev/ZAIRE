#ifndef GLOBAL_VAR_H
#define GLOGBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <esp_mac.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <driver/i2s.h>
#include <driver/uart.h>
#include <esp_log.h>
#include <esp_err.h>
#include <string.h>
#include <esp_camera.h>
#include <usb_device_uvc.h>
#include <uvc_frame_config.h>

//DEVICE TYPES
#define DEVICE_TYPE_SKI_GOGGLES     (0)
#define DEVICE_TYPE_BICYCLE_HELMET  (1)
#define DEVICE_TYPE_MOTOR_HELMET    (2)
#define DEVICE_TYPE_TEST            (100)

//AUDIO CHIP
#define AUDIO_CHIP_NONE             0x00
#define AUDIO_CHIP_BK3266           0x01


#define AUDIO_CHIP      AUDIO_CHIP_BK3266
#define DEVICE_TYPE     DEVICE_TYPE_BICYCLE_HELMET// Must come before zaire_system.h -- avoid loop defination
#include <zaire_system.h>

//GPIO
esp_err_t gpio_pin_init(void);

//UART
#define UART_TARGET_BK   "B"
#define H3_UART_NUM      UART_NUM_0
#define H3_TX            GPIO_NUM_43
#define H3_RX            GPIO_NUM_44
#define H3_BAUD          1200
#define HOST_UART_NUM    UART_NUM_1
#define HOST_TX          GPIO_NUM_48
#define HOST_RX          GPIO_NUM_47
#define HOST_BAUD        4800
#define AUDIO_UART_NUM   UART_NUM_2
#define BK_TX            GPIO_NUM_39
#define BK_RX            GPIO_NUM_42
#define BK_BAUD          9600
#define BUF_SIZE         1024
esp_err_t uart_init(void);
void host_uart_received(const char* str);
void host_uart_write_str(const char* str);
void host_uart_write_int(int data);
void bk_uart_snd(const char* str);
void bk_uart_received(const char* str);


//USB-CAM
#define PWDN_GPIO_NUM               (-1)
#define RESET_GPIO_NUM              (-1)
#define XCLK_GPIO_NUM               GPIO_NUM_15
#define SIOD_GPIO_NUM               GPIO_NUM_4
#define SIOC_GPIO_NUM               GPIO_NUM_5

#define Y9_GPIO_NUM                 GPIO_NUM_16
#define Y8_GPIO_NUM                 GPIO_NUM_17
#define Y7_GPIO_NUM                 GPIO_NUM_18
#define Y6_GPIO_NUM                 GPIO_NUM_12
#define Y5_GPIO_NUM                 GPIO_NUM_10
#define Y4_GPIO_NUM                 GPIO_NUM_8
#define Y3_GPIO_NUM                 GPIO_NUM_9 // 1
#define Y2_GPIO_NUM                 GPIO_NUM_11 //0

#define VSYNC_GPIO_NUM              GPIO_NUM_6
#define HREF_GPIO_NUM               GPIO_NUM_7
#define PCLK_GPIO_NUM               GPIO_NUM_13
#define UVC_MAX_FRAMESIZE_SIZE      (60*1024)
esp_err_t usb_init(void);
esp_err_t camera_init(void);
uvc_fb_t* camera_fb_get_cb(void *cb_ctx);
void camera_fb_return_cb(uvc_fb_t *fb, void *cb_ctx);
void camera_stop_cb(void *cb_ctx);
esp_err_t camera_start_cb(uvc_format_t format, int width, int height, int rate, void *cb_ctx);

//Task
#define TASK_HOLD_DELAY             (10)
#define TASK_HOLD_DELAY_FIVE_SEC    (1000 * 5)
#define TASK_HOLD_DELAY_MINUTE      (1000 * 60)
extern TaskHandle_t gpio_task_handler;
extern TaskHandle_t host_task_handler;
extern TaskHandle_t bk_task_handler;
extern TaskHandle_t h3_task_handler;
extern TaskHandle_t i2c_task_handler;
extern TaskHandle_t walkie_task_handler;
void gpio_run_task(void *vpParam);
void host_run_task(void *vpParam);
void bk_run_task(void *vpParam);
void h3_run_task(void *vpParam);
void i2c_run_task(void *vpParam);
void walkie_run_task(void *vpParam);

#if DEVICE_TYPE == DEVICE_TYPE_TEST
    void test_run_task(void *vpParam);
#endif

#endif