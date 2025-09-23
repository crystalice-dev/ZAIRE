#ifndef GLOBAL_VAR_H
#define GLOABL_VAR_H

#include "zaire_system.h"
#include "dns_server.h"
#include "BK3266_cmd_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <esp_flash.h>
#include <esp_wifi.h>
#include <esp_netif.h>
#include <esp_now.h>
#include <esp_mac.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_spiffs.h>
#include <esp_event.h>
#include <esp_http_server.h>
#include <esp_netif_ip_addr.h>
#include <esp_system.h>
#include <esp_spiffs.h>
#include <lwip/sockets.h>
#include <lwip/inet.h>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/i2s.h>
#include <driver/uart.h>
#include <driver/spi_master.h>
#include <wear_levelling.h>
#include "u8g2.h"
#include <u8g2_esp32_hal.h>
#include "esp_camera.h"
#include "max1704x.h"

//<------------- TIER SELECTION ------------->//
#define TIER SUMMIT
//<------------------- END ------------------>//

//NETWORK
#define NETWORK_MAX_CONN            9
#define NETWORK_SETTINGS_SSID       "ZAIRE_SETTING"
esp_err_t network_init();
esp_err_t network_settings_mode();
esp_err_t network_standard_mode();
esp_err_t network_pairing_mode_master();
esp_err_t network_pairing_mode_slave();
void wifi_send_ap_bssid();
esp_err_t esp_now_mesh_init(void);
void send_data_to_mesh(uint8_t data);
void detach_peer_from_mesh(uint8_t position);
void peer_leave_mesh(void);
void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
void esp_now_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len);

//PEER MESH SYSTEM
#define DEVICE_PAIRING_NAME         "zaireVISIONPairing_0" 
#define ESP_NOW_CHANNEL             1
#define DEFAULT_SCAN_LIST_SIZE      10
#define WALKIE_REQUEST_STA_MAC      0xA1
#define WALKIE_PAIRING_START        0xB0 //Alert pairing session has begun
#define WALKIE_PAIRING_DONE         0xB1 //Alert pairing session done
#define WALKIE_PAIRING_CANCEL       0xB3 //Alert pairing session being canceled
#define WALKIE_REMOVE_PEER_P0       0xC0 //Alert other devices to remove us from mesh - POSITION 0 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P1       0xC1 //Alert other devices to remove us from mesh - POSITION 1 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P2       0xC2 //Alert other devices to remove us from mesh - POSITION 2 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P3       0xC3 //Alert other devices to remove us from mesh - POSITION 3 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P4       0xC4 //Alert other devices to remove us from mesh - POSITION 4 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P5       0xC5 //Alert other devices to remove us from mesh - POSITION 5 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P6       0xC6 //Alert other devices to remove us from mesh - POSITION 6 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P7       0xC7 //Alert other devices to remove us from mesh - POSITION 7 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P8       0xC8 //Alert other devices to remove us from mesh - POSITION 8 [peer_mesh_position]

extern uint8_t new_peers;
extern uint8_t device_sta_mac[6];
extern uint8_t peer_addresses[NETWORK_MAX_CONN][6];
extern uint8_t peers_in_mesh; // 1 is us
extern uint8_t peer_mesh_position; // our position in mesh -> important for removal 

void request_sta_mac_addr(uint8_t *mac_addr);
void add_pairing_new_mesh(uint8_t *addr);

//WALKIE-TALKIE
#define WALKIE_INCLUDED
#define WALKIE_I2S_BCK_MIC              GPIO_NUM_2
#define WALKIE_I2S_BCK_SPK              GPIO_NUM_39
#define WALKIE_I2S_WS_MIC               GPIO_NUM_3
#define WALKIE_I2S_WS_SPK               GPIO_NUM_40
#define WALKIE_I2S_MIC                  GPIO_NUM_43
#define WALKIE_I2S_SPK                  GPIO_NUM_44

extern bool walkie_speak;
extern bool sendOver;
extern bool recOver;
extern bool speakOut;

esp_err_t init_walkie(void);
esp_err_t i2s_init(void);
void walkie_pairing_sequence(void);
void walkie_pairing_master(void);
void walkie_pairing_slave(void);
void walkie_pairing_sync_master(void);
void walkie_pairing_sync_slave(uint8_t *addr);
void walkie_discover_peers(void);
void walkie_pairing_close_down(void); //Turn off display after pairing session
void walkie_pairing_cancel_master(void); //Cancel pairing session MASTER
void walkie_pairing_cancel_slave(void); //Cancel pairing session SLAVE
void walkie_mute(void);

//BUZZER
#define BUZZER_INCLUDED
#include "driver/ledc.h"
#define BUZZER_FREQ_HZ      2000  // Default tone
#define BUZZER_DUTY         6144  // Duty out of 8192 (75%)
#define BUZZER_LEDC_CHANNEL LEDC_CHANNEL_0
#define BUZZER              GPIO_NUM_47
esp_err_t buzzer_init();
void buzzer_off();
void buzzer_on();
void quick_buzz();
void double_quick_buzz();

//DNS-CAPTIVE-PORTAL
extern TaskHandle_t dns_task_handle;
extern httpd_handle_t web_server;

httpd_handle_t start_webserver(void);
esp_err_t main_page_get_handler(httpd_req_t *req);

//CAMERA
#define CAMERA_INCLUDED
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
#define CAMERA_I2C_NUM              
esp_err_t init_camera(void);


//GPIOs
esp_err_t init_gpio();

//BK3266
#define BK3266_UART_RX      GPIO_NUM_42
#define BK3266_UART_TX      GPIO_NUM_41
#define BK3266_UART_BAUD    9600
#define BK3266_UART_NUM     UART_NUM_1
#define RX_BUF_SIZE         2048
esp_err_t init_uart();
esp_err_t init_bk3266(void);
void bk3266_send_cmd(const char *cmd);
void bk3266_set_bt_name(const char *name);
void bk3266_PP_CALL(void);

//MAX17043


//DISPLAY
extern u8g2_t display;
extern bool display_en;
esp_err_t init_display();
void display_welcome_animation(void);
void display_off(void);
    void display_welcome_animation(void);
    void display_main_UI(void);
    void init_display_gpio(void);
    void display_power_on(void);
    void display_power_off(void);
        //DISPLAY ELEMENTS
        void display_datetime();
        void display_location();
        void display_elevation();
        void display_battery(uint8_t percent);
        void display_camera_icon(void);
        void draw_walkie_on(void);
        void draw_walkie_off(void);

        //PASSS
        void display_quick_show(void);
        //FULL SCREEN DISPLAY 
        void display_low_battery_warning(void);
        void display_dns_setting(void);
        void display_walkie_MASTER_setting(void);
        void display_walkie_SLAVE_setting(void);
        void display_walkie_SYNC_setting(void);
        void display_show_walkie_paired_setting(void);
        void display_show_cancled(void);
        void display_show_walkie_master_search_setting(void);
        void display_show_walkie_slave_search_setting(void);
        void display_show_walkie_mute_sequence(void);
        void display_show_walkie_delete_sequence(void);
        void display_show_walkie_enter_pairing_sequence(void);
//TASKs
extern TaskHandle_t walkie_btn_task_handler;
extern TaskHandle_t purpose_left_btn_task_handler;
extern TaskHandle_t purpose_right_btn_task_handler;
extern TaskHandle_t display_task_handler;
extern TaskHandle_t bk3266_task_handler;
extern TaskHandle_t walkie_task_handler;

void walkie_btn_task_run(void *vpParam);
void purpose_left_btn_task_run(void *vpParam);
void purpose_right_btn_task_run(void *vpParam);
void display_task_run(void *vpParam);
void bk3266_task_run(void *vpParam);
void walkie_task_run(void *vpParm);

#endif