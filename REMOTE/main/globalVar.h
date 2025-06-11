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
#include <string.h>
#include <esp_netif.h>

extern uint8_t device_sta_mac[6];
extern uint8_t helmet_ap_mac[6];
extern bool isPairingInvoked; // Flag to indicate if pairing is invoked

// Inits
esp_err_t init_wifi(void);
esp_err_t espNow_init(void);
esp_err_t gpio_init(void);

//ESP-NOW
void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
esp_now_recv_cb_t esp_now_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len);

//Network
#define ESP_NOW_CHANNEL    7
#define DEFAULT_SCAN_LIST_SIZE      10
#define DEVICE_PAIRING_NAME         "Zaire_Remote_Pairing_01" // SSID for pairing
#define DEFAULT_SCAN_LIST_TIMEOUT   5000 // Timeout for scanning APs in milliseconds
#define REMOTE_REQUEST_STA_MAC      0x01 // Request STA MAC address command
void remote_pairing(void);
void request_sta_mac_addr(uint8_t *mac_addr);

//GPIO
#define TOP_BTN             GPIO_NUM_2
#define LEFT_BTN            GPIO_NUM_3
#define RIGHT_BTN           GPIO_NUM_4
#define LEFT_LED            GPIO_NUM_13
#define RIGHT_LED           GPIO_NUM_14
#define TOP_LED             GPIO_NUM_15

//LEDs
typedef enum {
    LED_OFF = 0,
    LED_STANDBY = 1,
    LED_BLINK = 2,
    LED_BLINK_FAST = 3,
} led_blink_state_t;
extern led_blink_state_t top_led_state;
extern led_blink_state_t left_led_state;
extern led_blink_state_t right_led_state;

//I2C
#define I2C_MASTER_SCL_IO   GPIO_NUM_17
#define I2C_MASTER_SDA_IO   GPIO_NUM_16
#define I2C_MASTER_NUM      I2C_NUM_0
#define I2C_MASTER_FREQ_HZ  100000

//Tasks
extern TaskHandle_t gpio_top_btn_task_handler;
extern TaskHandle_t gpio_left_btn_task_handler;
extern TaskHandle_t gpio_right_btn_task_handler;
extern TaskHandle_t gpio_left_led_task_handler;
extern TaskHandle_t gpio_right_led_task_handler;
extern TaskHandle_t gpio_top_led_task_handler;

void gpio_top_btn_run_task(void *vpParam);
void gpio_left_btn_run_task(void *vpParam);
void gpio_right_btn_run_task(void *vpParam);
void gpio_left_led_run_task(void *vpParam);
void gpio_right_led_run_task(void *vpParam);
void gpio_top_led_run_task(void *vpParam);


#endif