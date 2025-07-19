#ifndef GLOBAL_VAR_H
#define GLOABL_VAL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/i2s.h>
#include <driver/uart.h>
#include <driver/ledc.h>
#include <esp_spiffs.h>
#include <esp_event.h>
#include <esp_check.h>
#include <sys/param.h>
#include <esp_http_server.h>
#include <esp_netif.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <math.h>
#include <esp_err.h>
#include <esp_log.h>
#include <u8g2.h>
#include <u8g2_esp32_hal.h>
//#include "dns_server.h"


//ZAIRE SYSTEM
#define DEVICE_TYPE     DEVICE_TYPE_BICYCLE_HELMET// Must come before zaire_system.h -- avoid loop defination
#define HIGH        1
#define LOW         0
extern bool demo_mode;


//REMOTE
#define REMOTE_INCLUDED

//DISPLAY 
#define DISPLAY_INCLUDED
#include <u8g2.h>
#include <u8g2_esp32_hal.h>
#define DISPLAY_EN_PIN     GPIO_NUM_18
#define I2C_1_SDA           GPIO_NUM_4
#define I2C_1_SCL           GPIO_NUM_5
typedef enum {
    DISPLAY_EN_OFF = 0,
    DISPLAY_MAIN_UI = 1,
    DISPLAY_SHOW_LOW_BAT = 2,
    DISPLAY_SHOW_DNS_SETTING = 3,
    DISPLAY_SHOW_WALKIE_PAIRING = 4,
    DISPLAY_SHOW_BLUETOOTH_PAIRING = 5,
}display_target_t;
extern display_target_t display_target;

extern bool display_en; // Rather the display is on or not 
extern u8g2_t display;
esp_err_t display_init(void);
void display_clear(void);
void display_welcome_animation(void);
void display_main_UI(void);
void init_display_gpio(void);
void display_power_on(void);
void display_power_off(void);
    //DISPLAY ELEMENTS
    void display_datetime();
    void display_walkie_paired();
    void display_location();
    void display_elevation();
    void display_battery(uint8_t percent);
    void display_camera_icon(void);

    //PASSS
    void display_quick_show(void);
    //FULL SCREEN DISPLAY 
    void display_low_battery_warning(void);
    void display_dns_setting(void);
    void display_show_walkie_pairing(void);
    void display_show_bluetooth_pairing(void);

//WALKIE
 #define WALKIE_PAIRING_MASTER     "P0"
#define WALKIE_PAIRING_SLAVE      "P1"
#define WALKIE_PAIRING_SYNC       "P2"
#define WALKIE_PAIRING_COMPLETE   "P3"
#define WALKIE_MUTE_ON            "B1"
#define WALKIE_MUTE_OFF           "B0"
#define DEVICE_PAIRING_NAME         "zairehelmetsPairing_0" 
#define ESP_NOW_CHANNEL             1
#define DEFAULT_SCAN_LIST_SIZE      10
#define WALKIE_BCK                  GPIO_NUM_1
#define WALKIE_WS                   GPIO_NUM_2
#define WALKIE_DIN                  GPIO_NUM_3
#define WALKIE_DOUT                 GPIO_NUM_14
#define SAMPLE_RATE                 15500 //15500
#define WALKIE_REQUEST_STA_MAC      0xB1
#define WALKIE_NEW_MESH             0xF5
#define WALKIE_PAIRING_DONE         0xA2
typedef enum{
    NONE = 0,
    MASTER = 1,
    SLAVE = 2,
    SYNC = 3
}walkie_pairing_mode_t;
extern walkie_pairing_mode_t walkie_pairing_mode;
extern uint8_t device_sta_mac[6];
extern uint8_t peer_addresses[8][6];
extern uint8_t temp_peer_addr[6];
extern uint8_t number_paired_peers;
extern uint8_t new_peers;
extern bool mesh_system_active;
extern bool sendOver;
extern bool recOver;
extern bool speakOut;
extern bool walkie_mute;
extern bool walkie_paired;
extern int32_t *samples_32bit;
extern int16_t *samples_16bit;
extern uint8_t *samples_8bit ;
extern int16_t *recive_16bit;
extern int16_t *output_16bit;
extern const i2s_port_t REC_I2S_PORT;
extern const i2s_port_t SPK_I2S_PORT;
void I2SInit();
int I2Sread(int16_t *samples, int count);
void covert_bit(int16_t *temp_samples_16bit,uint8_t*temp_samples_8bit,uint8_t len );
void I2Swrite(int16_t *samples, int count);
esp_err_t init_wifi(void);
esp_err_t station_reconfig(void);
esp_err_t master_reconfig(void);
esp_err_t slave_reconfig(void);
esp_err_t init_esp_now(void);
void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
esp_now_recv_cb_t esp_now_recv_cb(const uint8_t *mac_addr,  const uint8_t *data, int data_len);
void walkie_snt(const uint8_t *i2s_data, uint16_t i2s_len);
void walkie_rcvd(uint16_t i2s_data);
void walkie_discover_peers(void);
void request_sta_mac_addr(uint8_t *addr);
esp_err_t remove_peer_from_mesh(uint8_t *addr);
void walkie_pairing_master(void);
void walkie_pairing_slave(void);
void walkie_pairing_sync(uint8_t *addr);
void walkie_pairing_max(uint8_t *addr);
void walkie_pairing_new_mesh(uint8_t *addr);

//BUZZER
#define BUZZER_INCLUDED
#define BUZZER_FREQ_HZ      2000  // Default tone
#define BUZZER_DUTY         4096  // Duty out of 8192 (50%)
#define BUZZER_LEDC_CHANNEL LEDC_CHANNEL_0
#define BUZZER GPIO_NUM_40
void buzzer_init();
void buzzer_off();
void buzzer_on();
void quick_buzz();
void double_quick_buzz();

//GPIOs
#define PURPOSE_BTN     GPIO_NUM_15
#define WALKIE_BTN      GPIO_NUM_7
esp_err_t gpio_pin_init(void);



//BLINDSPOT
#define BLINDSPOT_INCLUDED
#include <esp_timer.h>
#include "esp_rom_sys.h"
#define BS_ECHO_RIGHT   GPIO_NUM_46
#define BS_ECHO_LEFT    GPIO_NUM_45
#define BS_TRIG_RIGHT   GPIO_NUM_48
#define BS_TRIG_LEFT    GPIO_NUM_47
#define BS_LED_RIGHT    GPIO_NUM_39
#define BS_LED_LEFT     GPIO_NUM_38
#define MAX_DISTANCE_CM       600  // Maximum measurable distance in cm
#define MIN_DETECT_DISTANCE   -1 //ft - When the helmet alert rider of potential object (4 - motorcycle 2 bicycle) -- to be tested
#define MAX_DETECT_DISTANCE   15 //ft - When the helmet does not alert rider of potential object (6 - motorcycle 4 bicycle) -- to be tested
#define TIMEOUT_US            (MAX_DISTANCE_CM * 58) 
extern int32_t  bs_rt_distance;
extern int32_t  bs_lt_distance;
void bs_monitor_init();
int32_t bs_lt_get_distance(void);
int32_t bs_rt_get_distance(void);
void set_BS_led_left(uint8_t duty);
void set_BS_led_right(uint8_t duty); 
void set_BS_led_brightness(uint8_t duty_right, uint8_t duty_left);
//Lights
#include "led_strip.h"
#define LIGHTS_INCLUDED
#define BACK_LED        GPIO_NUM_1
#define FRONT_WHITE_LED GPIO_NUM_2
//#define FRONT_RED_LED   GPIO_NUM_42
#define LED_STRIP_LED_NUMBERS 10
#define LED_STRIP_RMT_RES_HZ  (10 * 1000 * 1000)
#define AMBER_R 255
#define AMBER_G 100
#define AMBER_B 0
typedef enum{
    NORMAL = 0,
    MASTER_PAIRING = 1,
    SLAVE_PAIRING = 2,
    SYNC_PAIRING = 3,
    REMOTE_PAIRING = 4,
    BLUETOOTH_PAIRING = 5
}led_target_stage_t;
extern led_target_stage_t led_target_stage;
typedef enum {
    LED_OFF = 0,
    FRONT_WHITE_ON = 1,
    FRONT_WHITE_PWM = 2,
    LOW_BATTERY = 3,
    BACK_BRAKE_ON = 1,
    LEFT_TURN = 2,
    RIGHT_TURN = 3,
}led_target_mode_t;
extern led_target_mode_t led_target_mode[2];
led_strip_handle_t configure_led_stip();
void led_welcome_animation(led_strip_handle_t led_strip);
void led_front_white_on(void);
void led_front_white_off(void);
void led_front_white_pwm(void);
void led_battery_low_on(void);
void led_battery_low_off(void);
void led_right_turn(led_strip_handle_t led_strip);
void led_left_turn(led_strip_handle_t led_strip);
void led_brake_red(led_strip_handle_t led_strip);
void led_pairing_master_search_blue(led_strip_handle_t led_strip);
void led_pairing_slave_search_blue(led_strip_handle_t led_strip);
void led_pairing_sync_blue(led_strip_handle_t led_strip);
void led_pairing_complete(led_strip_handle_t led_strip);
void led_pairing_remote(led_strip_handle_t led_strip);
void led_pairing_bluetooth(led_strip_handle_t led_strip);
void led_off_all(led_strip_handle_t led_strip);
void led_demo_operation(led_strip_handle_t led_strip);





//TASKS
#define TASK_HOLD_DELAY             (10)
#define TASK_HOLD_DELAY_FIVE_SEC    (1000 * 5)
#define TASK_HOLD_DELAY_MINUTE      (1000 * 60)
extern TaskHandle_t gpio_purpose_btn_task_handler;
extern TaskHandle_t gpio_walkie_btn_task_handler;
extern TaskHandle_t gps_uart_task_handler;
extern TaskHandle_t h3_uart_task_handler;
extern TaskHandle_t walkie_uart_task_handler;
extern TaskHandle_t i2c_task_handler;
extern TaskHandle_t display_task_handler;
extern TaskHandle_t led_strip_task_handler;
extern TaskHandle_t bs_left_monitor_handler;
extern TaskHandle_t display_camera_btn_task_handler;
extern TaskHandle_t bs_right_monitor_handler;
extern TaskHandle_t walkie_task_handler;
void gpio_purpose_run_task(void *vpParam);
void gpio_walkie_run_task(void *vpParam);
void gps_uart_run_task(void *vpParam);
void h3_uart_run_task(void *vpParam);
void walkie_uart_run_task(void *vpParam);
void i2c_run_task(void *vpParam);
void display_run_task(void *vpParam);
void led_strip_run_task(void *vpParam);
void bs_left_monitor_task(void *vpParam);
void bs_right_monitor_task(void *vpParam);
void display_camera_btn_run_task(void *vpParam);
void walkie_run_task(void *vpParam);



#endif 