#ifndef GLOBAL_VAR_H
#define GLOGBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <nvs_flash.h>
#include <esp_err.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <esp_mac.h>

extern uint8_t device_sta_mac[6];
extern uint8_t helmet_ap_mac[6];

// Inits
esp_err_t init_wifi(void);
esp_err_t espNow_init(void);
esp_err_t gpio_init(void);

//ESP-NOW
void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
esp_now_recv_cb_t esp_now_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len);

//Network
#define ESP_NOW_CHANNEL    7


//GPIO
#define TOP_BTN             GPIO_NUM_2
#define LEFT_BTN            GPIO_NUM_3
#define RIGHT_BTN           GPIO_NUM_4
#define LEFT_LED            GPIO_NUM_13
#define RIGHT_LED           GPIO_NUM_14
#define TOP_LED             GPIO_NUM_15

//I2C
#define I2C_MASTER_SCL_IO   GPIO_NUM_17
#define I2C_MASTER_SDA_IO   GPIO_NUM_16
#define I2C_MASTER_NUM      I2C_NUM_0
#define I2C_MASTER_FREQ_HZ  100000
#endif