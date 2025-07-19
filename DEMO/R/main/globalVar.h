#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <esp_mac.h>
#include <esp_netif.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <freertos/task.h>

//SYSTEM
#define HIGH            1
#define LOW             0
#define TEST_LED        GPIO_NUM_15
extern bool pairing_mode;


//GPIOs
#define TOP_BTN         GPIO_NUM_2
#define LEFT_BTN        GPIO_NUM_4
#define RIGHT_BTN       GPIO_NUM_6
#define TOP_LED         GPIO_NUM_3
#define LEFT_LED        GPIO_NUM_5
#define RIGHT_LED       TEST_LED//GPIO_NUM_7
#define BUZZER          GPIO_NUM_12
esp_err_t gpio_init(void);

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

//Turn Signals
extern bool left_turn_on;
extern bool right_turn_on;


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