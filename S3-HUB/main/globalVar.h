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