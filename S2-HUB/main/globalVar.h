#ifndef GLOBAL_VAR_H
#define GLOGBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <driver/gpio.h>
#include <driver/i2s.h>
#include <nvs_flash.h>
#include <esp_err.h>
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>
#include <usb_device_uac.h>  
#include <string.h>


//Device
#include <zaire_system.h>
#define DEVICE_TYPE DEVICE_TYPE_SKI_GOGGLES


// USB-MIC
#define SAMPLE_RATE (16000)
#define I2S_PORT    I2S_NUM_0
#define I2S_CLK     GPIO_NUM_1
#define I2S_WS      GPIO_NUM_2
#define I2S_DIN     GPIO_NUM_3
extern const i2s_config_t i2s_config;
extern const i2s_pin_config_t i2s_pin_config;
esp_err_t init_i2s(void);
esp_err_t init_usb_mic(void);
int uac_device_input_cb(uint8_t *buf, size_t len, size_t *bytes_read, void *arg);
#endif