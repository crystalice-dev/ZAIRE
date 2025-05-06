#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <driver/gpio.h>
#include <driver/i2s.h>
#include <driver/i2c.h>
#include <nvs_flash.h>
#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_spiffs.h>
#include <math.h>
#include <usb_device_uac.h>  
#include <string.h>
#include <esp_event.h>
#include <esp_wifi.h>
#include <esp_check.h>
#include <esp_http_server.h>
#include <esp_netif.h>
#include <sys/param.h>
#include <dns_server.h>


//DEVICE
#define DEVICE_TYPE         1  // Must come before zaire_system.h -- avoid loop defination
#include <zaire_system.h>
extern bool WALKIE_STATUS;

//GPS
#define GPS_TX  GPIO_NUM_16
#define GPS_RX  GPIO_NUM_17
extern char* gps_latitude;
extern char* gps_longitude;
extern char* gps_elevation;


//BMS -- BATTERY
extern uint8_t BATTERY_STATUS;

//TEMP
extern uint8_t TEMP_STATUS;


//DISPLAY
#ifdef DISPLAY_INCLUDED
    #include <u8g2.h>
    #include <u8g2_esp32_hal.h>
    #define DISPLAY_EN_PIN     GPIO_NUM_18
    #define DISPLAY_EN_BTN     GPIO_NUM_8

    typedef enum {
        DISPLAY_EN_OFF = 0,
        DISPLAY_MAIN_UI = 1,
        DISPLAY_SHOW_LOW_BAT = 2,
        DISPLAY_SHOW_DNS_IP = 3,
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
        void display_battery(uint8_t percent);
        void display_camera_icon(void);

        //PASSS
        void display_quick_show(void);
        //FULL SCREEN DISPLAY 
        void display_low_battery_warning(void);
        void display_dns_IP(void);
#elif // ADD I2C TO I2C_NUM_1
#endif

//NETWORK
#define EXAMPLE_MAX_STA_CONN 4
extern char *WIFI_SSID;
esp_err_t wifi_init();

//DNS-CAPTIVE-PORTAL
extern TaskHandle_t dns_task_handle;
extern httpd_handle_t web_server;

httpd_handle_t start_webserver(void);
esp_err_t main_page_get_handler(httpd_req_t *req);
esp_err_t js_handler(httpd_req_t *req);
esp_err_t css_handler(httpd_req_t *req);
esp_err_t ping_handler(httpd_req_t *req);
esp_err_t update_post_handler(httpd_req_t *req);



//NVS -- Non-Volatile Storage
#define WALKIE_NVS_NAMESPACE        "walkie"
#define REMOTE_NVS_NAMESPACE        "remote"
#define SERVER_NVS_NAMESPACE        "server"
#define WALKIE_ADDR_KEY             "isWalkieAddrIn"
#define REMOTE_ADDR_KEY             "isRemoteAddrIn"
#define REMOTE_AP_ADDR_KEY          "remoteAP"
#define REMOTE_STA_ADDR_KEY         "remoteSTA"
extern nvs_handle_t walkie_addr_nvs_registered;
extern nvs_handle_t remote_addr_nvs_registered;
extern nvs_handle_t server_nvs_handler;
extern uint8_t n_value; // place holder for NVS_read();
esp_err_t NVS_init(void);
esp_err_t NVS_start(const char *namespace, const nvs_handle_t *handler); // Open NVS
esp_err_t NVS_write(nvs_handle_t handler, const char *key, uint8_t value);
esp_err_t NVS_erase(nvs_handle_t handler, const char *key);
esp_err_t NVS_close(nvs_handle_t handler);
uint8_t NVS_read(nvs_handle_t handler, const char *key);


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

//I2C
#define DS3231_ADDR         0x68
#define WORKING_I2C_NUM     I2C_NUM_1
#define I2C_1_SDA           GPIO_NUM_6
#define I2C_1_SCL           GPIO_NUM_7

// GLOBAL GPIOs
#define CAMERA_ON_PIN   GPIO_NUM_14
esp_err_t gpio_pin_init(void);

//RTC
char* _get_RTC_time();
char* _get_RTC_date();
esp_err_t set_RTC(uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
uint8_t dec_to_bcd(uint8_t val);
uint8_t bcd_to_dec(uint8_t val);

//TASKS
#define TASK_HOLD_DELAY             (10)
extern TaskHandle_t gpio_task_handler;
extern TaskHandle_t uart_task_handler;
extern TaskHandle_t display_task_handler;
void gpio_run_task(void *vpParam);
void uart_run_task(void *vpParam);
void display_run_task(void *vpParam);

#endif