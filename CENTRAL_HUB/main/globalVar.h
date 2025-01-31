#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "regex.h"
#include "nvs_flash.h"
#include "esp_random.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_now.h"
#include "esp_crc.h"
#include "driver/i2c.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_timer.h"
#include "peerGlobalCodeAddr.h"

//Device Info
#define DEVICE_NAME     "zairehelmets"
#define HIGH            1
#define LOW             0
extern bool first_boot;
int zaire_system_init();
int check_walkie_addr(); // checks if CENTRAL HUB has helmet's mac addr registered.

//NVS -- Non-Volatile Storage
#define WALKIE_NVS_NAMESPACE        "walkie"
#define SERVER_NVS_NAMESPACE        "server"
#define WALKIE_ADDR_KEY             "isWalkieAddrIn"
extern nvs_handle_t walkie_addr_nvs_registered;
extern nvs_handle_t server_nvs_handler;
extern uint8_t n_value; // place holder for NVS_read();
bool nvs_start(const char *namespace, const nvs_handle_t *handler); // Open NVS
uint8_t nvs_read(nvs_handle_t handler, const char *key);
bool nvs_write(nvs_handle_t handler, const char *key, uint8_t value);
bool NVS_erase(nvs_handle_t handler, const char *key, uint8_t value);
bool NVS_close(nvs_handle_t handler, const char *key, uint8_t value);


//Peer Mesh System
//Peer Mesh System
extern bool is_master_mode; // 1 - MASTER || 0 - SLAVE
extern bool isCompactOn; // Rather we are have an outside device in the Network to watch for ie Cardo, Sena, etc...
extern uint8_t walkie_address[6]; // Getting unit's walkie MAC addr from NVS -- Only if walkie_addr_nvs_registered = 1
extern uint8_t walkie_interject_number; // has to be 6
extern uint8_t number_paired_peers;
extern uint8_t number_paired_peers_walkie_addr_rec;
extern uint8_t bt_addr[6]; // Only if "isCompactOn" == 1
extern uint8_t peer_addresses[18][6]; // Up to 18
extern uint8_t peer_walkie_addresses[18][6]; // Up to 18
extern uint8_t peers_number_helmets; //Numeber of helmets in mesh connection
extern uint8_t peers_slave_number_hierachy; // if slave --> hierachy number: 2-8 || if master --> hierachy number: 1
extern uint8_t peers_hemets_controller_mac[8][6]; //MAC addr of connected helmets controllers
extern uint8_t peers_helmets_walkie_mac[8][6]; // MAC addr of connected helmet walkie >> to send to our walkie <<
void peer_extract_slave_walkie_addr(void); // Gather all slaves walkie 
void peer_received_slave_walkie_addr(void); // Walkie addr from slaves
esp_err_t espNow_add_peer(const uint8_t *mac_addr, uint8_t channel);
typedef struct {
    bool unicast;                         //Send unicast ESPNOW data.
    bool broadcast;                       //Send broadcast ESPNOW data.
    uint8_t state;                        //Indicate that if has received broadcast ESPNOW data or not.
    uint32_t magic;                       //Magic number which is used to determine which device to send unicast ESPNOW data.
    uint16_t count;                       //Total count of unicast ESPNOW data to be sent.
    uint16_t delay;                       //Delay between sending two ESPNOW data, unit: ms.
    int len;                              //Length of ESPNOW data to be sent, unit: byte.
    uint8_t *buffer;                      //Buffer pointing to ESPNOW data.
    uint8_t dest_mac[ESP_NOW_ETH_ALEN];   //MAC address of destination device.
} example_espnow_send_param_t;


//GPIOs
#define WALKIE_BTN                      GPIO_NUM_23 // Default Walkie BTN
#define PURPOSE_BTN                     GPIO_NUM_15 // Default PRIME BTN
#define PURPOSE_LED                     GPIO_NUM_2    
#define BUZZER_PIN                      GPIO_NUM_5 // Across all boards


//Emergency
#define EMERG_PIN                       GPIO_NUM_19

//BlindSpot Monitoring
#define BS_RT_TRIG_PIN                  GPIO_NUM_33
#define BS_LT_TRIG_PIN                  GPIO_NUM_32
#define BS_RT_ECHO_PIN                  GPIO_NUM_39
#define BS_LT_ECHO_PIN                  GPIO_NUM_36
#define BS_RT_LED_PIN                   GPIO_NUM_25 // LEDC channel 0
#define BS_LT_LED_PIN                   GPIO_NUM_26 // LEDC channel 1
#define MAX_DISTANCE_CM                 600  // Maximum measurable distance in cm
#define MIN_DETECT_DISTANCE             -1 //ft - When the helmet alert rider of potential object (4 - motorcycle 2 bicycle) -- to be tested
#define MAX_DETECT_DISTANCE             15 //ft - When the helmet does not alert rider of potential object (6 - motorcycle 4 bicycle) -- to be tested
#define TIMEOUT_US                      (MAX_DISTANCE_CM * 58)  // Timeout in microseconds
extern int32_t  bs_rt_distance;
extern int32_t  bs_lt_distance;
int bs_monitor_init();
int32_t bs_rt_get_distance(void);
uint8_t bs_lt_get_distance(void);
void bs_right_monitor_task(void *vpParam);
void bs_left_monitor_task(void *vpParam);

int gpio_pin_set_up(void);
void quick_led_flash(uint8_t n);
void buzz(void);

//I2C
#define I2C_DATA                        GPIO_NUM_21
#define I2C_SCL                         GPIO_NUM_22
int init_i2c();

//UART
#define PI_UART_RX                      -1
#define PI_UART_TX                      GPIO_NUM_1 
#define PI_BAUD_RATE                    9600
#define PI_UART_NUM                     UART_NUM_0  // UART port number (UART0)
#define WALKIE_UART_RX                  GPIO_NUM_16
#define WALKIE_UART_TX                  GPIO_NUM_17
#define WALKIE_BAUD_RATE                115200
#define WALKIE_UART_NUM                 UART_NUM_1 // UART port number (UART1)
#define BUF_SIZE                        1024       
extern bool walkie_get_addr_port;
extern bool bt_read_data_raw;
extern bool walkie_read_data_raw;
extern bool pi_read_data_raw;
int uart_init(void);
void pi_uart_snd(const int data);
void walkie_uart_snd(const int data);
void walkie_uart_rec(const char *str);
void walkie_uart_handler_int(uint8_t data);

//Tasks
void gpio_run_task(void *vpParam);
void uart_run_task(void *vpParam);

#endif