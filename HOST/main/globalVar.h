#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <driver/gpio.h>
#include <driver/i2s.h>
#include <driver/i2c.h>
#include <driver/uart.h>
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
#define PURPOSE_BTN     GPIO_NUM_15

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



//UART
#define UART_TARGET_BK  "B"
#define GPS_UART_NUM    UART_NUM_2
#define GPS_TX          GPIO_NUM_17
#define GPS_RX          GPIO_NUM_16
#define GPS_BAUD        9600
#define WALKIE_UART_NUM UART_NUM_1
#define WALKIE_TX       GPIO_NUM_9
#define WALKIE_RX       GPIO_NUM_10
#define WALKIE_BAUD     4800
#define H3_UART_NUM     UART_NUM_0
#define H3_TX           GPIO_NUM_43
#define H3_RX           GPIO_NUM_44
#define H3_BAUD         115200
#define BUF_SIZE        1024
esp_err_t uart_init(void);
void walkie_uart_received(const char* str);
void walkie_uart_write_str(const char* str);
void walkie_uart_write(int data);



//GPS
#define GPS_LAT_LON_SPEED_CODE "$GPRMC"
#define GPS_ALT_CODE           "$GPGGA"
extern char gps_latitude[260];
extern char gps_longitude[260];
extern uint8_t gps_speed;
extern uint16_t gps_elevation;
extern bool gps_speed_type; // 0 - MPH 1 - KMH
extern bool gps_elevation_type; // 0 - Feet 1 - Meter

void gps_get_lat_lon_speed(const char* line);
void gps_get_alt(const char* line);
long gps_convert_M_2_FT(long elevation);
uint8_t gps_convert_KMH_2_MPH(uint8_t speed);
//BMS -- BATTERY
#define MAX17043_ADDR  0x36
extern float BATTERY_STATUS; // %
extern float BATTERY_VOLTAGE;
esp_err_t battery_init();
esp_err_t battery_read16(uint8_t reg, uint16_t *out_val);
esp_err_t battery_quick_start();
float battery_get_voltage();
float battery_get_soc();

//TEMP
extern uint8_t TEMP_STATUS;

//LIGHT
#define BH1750_ADDR 0x23 // or 0x5C depending on ADDR pin
extern float lux;
esp_err_t bh1750_init();
float bh1750_read_lux();

//NETWORK
#define EXAMPLE_MAX_STA_CONN 4
esp_err_t wifi_init();
esp_err_t wifi_settings_mode();

//DNS-CAPTIVE-PORTAL
extern TaskHandle_t dns_task_handle;
extern httpd_handle_t web_server;

httpd_handle_t start_webserver(void);
esp_err_t main_page_get_handler(httpd_req_t *req);

//NVS -- Non-Volatile Storage
#define WALKIE_NVS_NAMESPACE        "walkie"
#define REMOTE_NVS_NAMESPACE        "remote"
#define SERVER_NVS_NAMESPACE        "server"
#define WALKIE_ADDR_KEY             "isWalkieAddrIn"
#define REMOTE_ADDR_KEY             "isRemoteAddrIn"
#define REMOTE_AP_ADDR_KEY          "remoteAP"
#define REMOTE_STA_ADDR_KEY         "remoteSTA"

typedef struct {
    uint8_t WALKIE_STATUS, AUTO_DASHCAM, BLINDSPOT_MONITORING, AUTO_BACK_LIGHT, TURN_SIGNAL_DURATION;
    char DEVICE_NAME[1040];
    char WIFI_SSID[1040];
} settings_t;

extern settings_t system_settings;

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
esp_err_t NVS_readblob(nvs_handle_t handle, const char *key, void *out_struct, size_t expected_size);
esp_err_t NVS_writeblob(nvs_handle_t handle, const char *key, const void *in_struct, size_t size);
esp_err_t NVS_write_settings();


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
#define PARSE_I2C_NUM       I2C_NUM_0
#define WORKING_I2C_NUM     I2C_NUM_1
#define I2C_0_SDA           GPIO_NUM_13
#define I2C_0_SCL           GPIO_NUM_12
#define I2C_1_SDA           GPIO_NUM_6
#define I2C_1_SCL           GPIO_NUM_7
esp_err_t i2c_init(void);


// GLOBAL GPIOs
esp_err_t gpio_pin_init(void);

//RTC
char* _get_RTC_time();
char* _get_RTC_date();
esp_err_t set_RTC(uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t date, char* month, uint8_t year);
uint8_t dec_to_bcd(uint8_t val);
uint8_t bcd_to_dec(uint8_t val);
uint8_t _get_real_month(const char* month);

//TASKS
#define TASK_HOLD_DELAY             (10)
#define TASK_HOLD_DELAY_FIVE_SEC    (1000 * 5)
#define TASK_HOLD_DELAY_MINUTE      (1000 * 60)
extern TaskHandle_t gpio_task_handler;
extern TaskHandle_t gps_uart_task_handler;
extern TaskHandle_t h3_uart_task_handler;
extern TaskHandle_t walkie_uart_task_handler;
extern TaskHandle_t i2c_task_handler;
extern TaskHandle_t display_task_handler;
extern TaskHandle_t led_strip_task_handler;
extern TaskHandle_t bs_left_monitor_handler;
extern TaskHandle_t bs_right_monitor_handler;
void gpio_run_task(void *vpParam);
void gps_uart_run_task(void *vpParam);
void h3_uart_run_task(void *vpParam);
void walkie_uart_run_task(void *vpParam);
void i2c_run_task(void *vpParam);
void display_run_task(void *vpParam);
void led_strip_run_task(void *vpParam);
void bs_left_monitor_task(void *vpParam);
void bs_right_monitor_task(void *vpParam);


#if DEVICE_TYPE == DEVICE_TYPE_TEST
    void test_run_task(void *vpParam);
#endif

#endif