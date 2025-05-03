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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>
#include <usb_device_uac.h>  
#include <string.h>
#include <esp_event.h>
#include <esp_wifi.h>
#include <esp_check.h>
#include <esp_http_server.h>
#include <esp_netif.h>
#include <sys/param.h>
#include "SuperMon.h"
#include <dns_server.h>


//DEVICE
#define DEVICE_TYPE         1  // Must come before zaire_system.h -- avoid loop defination
#include <zaire_system.h>

//DISPLAY
#ifdef DISPLAY_INCLUDED
    #include <u8g2.h>
    #include <u8g2_esp32_hal.h>
    #define I2C_0_SDA GPIO_NUM_6
    #define I2C_0_SCL GPIO_NUM_7
    extern u8g2_t display;
    esp_err_t display_init(void);
#endif

//NETWORK
#define EXAMPLE_MAX_STA_CONN 4
extern char *WIFI_SSID;
esp_err_t wifi_init();

//DNS-CAPTIVE-PORTAL
extern TaskHandle_t dns_task_handle;
extern httpd_handle_t web_server;
httpd_handle_t start_webserver(void);
esp_err_t expose_main_menu_page(void);
esp_err_t expose_close_settings_page(void);
esp_err_t ping_handler(httpd_req_t *req);
esp_err_t update_post_handler(httpd_req_t *req);
esp_err_t hello_get_handler(httpd_req_t *req);


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
esp_err_t nvs_init(void);
esp_err_t nvs_start(const char *namespace, const nvs_handle_t *handler); // Open NVS
esp_err_t nvs_write(nvs_handle_t handler, const char *key, uint8_t value);
esp_err_t NVS_erase(nvs_handle_t handler, const char *key, uint8_t value);
esp_err_t NVS_close(nvs_handle_t handler, const char *key, uint8_t value);
uint8_t nvs_read(nvs_handle_t handler, const char *key);


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