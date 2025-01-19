#ifndef GLOBAL_VAR_H
#define GLOABL_VAR_H
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <driver/i2s.h>
#include <Wire.h>
#include <NewPing.h>
#include <BH1750.h>
#include <RTClib.h>
#include <TinyGPS++.h>
#include <EEPROM.h>


int zaire_system_init(void);

//UART
#define CENTRAL_UART_RX_PIN     GPIO_NUM_16
#define CENTRAL_UART_TX_PIN     GPIO_NUM_17
#define CENTRAL_BAUD_RATE       (115200)
#define GPS_UART_RX_PIN         GPIO_NUM_3
#define GPS_UART_TX_PIN         GPIO_NUM_1
#define GPS_BAUD_RATE           (9600)  
extern HardwareSerial serialCentral; //uart_num_1
extern HardwareSerial serialGPS;    //uart_num_0
extern bool central_read_data_raw;
void uart_init(void);
void central_uart_snd(const char *data);
void central_uart_rec(const char *data);
void uart_task(void *vpParam);

//EEPROM
#define EEPROM_SIZE      (512)
int start_EEPROM(void);


//GPIO
#define EMERG_PIN        GPIO_NUM_36 
#define PI_REC_SIG       GPIO_NUM_39
#define WALKIE_PIN       GPIO_NUM_23
#define BUZZER_PIN       GPIO_NUM_5
#define PURPOSE_LED      GPIO_NUM_2
int gpio_pin_set_up(void);

//I2C
#define I2C_0_DATA_PIN   GPIO_NUM_21
#define I2C_0_SCL_PIN    GPIO_NUM_22
#define I2C_1_DATA_PIN   GPIO_NUM_18
#define I2C_1_SCL_PIN    GPIO_NUM_19


//ES8311
#define ES8311_I2C_ADDR  0x18
#define I2S_WS_PIN       GPIO_NUM_27
#define I2S_BCK_PIN      GPIO_NUM_14
#define I2S_DIN_PIN      GPIO_NUM_12
#define I2S_DOUT_PIN     GPIO_NUM_13
extern TwoWire es8311_i2c;
int ES8311_init();

//SDCard
#define SD_SCL_PIN       GPIO_NUM_35
#define SD_CMD_PIN       GPIO_NUM_34
#define SD_D0_PIN        GPIO_NUM_15

//BlindSpot
#define LED_R_SIG        GPIO_NUM_32
#define LED_L_SIG        GPIO_NUM_33
#define BS_RIGHT_LED     GPIO_NUM_25
#define BS_LEFT_LED     GPIO_NUM_26
extern const int BS_RIGHT_LED_PWM;       // PWM channel (0-15)
extern const int BS_LEFT_LED_PWM;       // PWM channel (0-15)
extern const int pwmFrequency;  // PWM frequency in Hz
extern const int pwmResolution;    // PWM resolution in bits (1-16)
extern int pwmBSLightOn;
extern int pwmBSLightOff; 
extern uint8_t lightMode; // 1 - Day; 0 - Night
int blindspot_lights_init(void);

//ACCESSORIES
int accessories_init();

//Light Sensor BH1750
#define dayTimeLED            255;
#define nightTimeLED          75;
extern bool is_LIGHT_SENSOR_ACTIVE;
extern uint8_t lightMode; // 1 - Day; 0 - Night
extern BH1750 lightSensor;
void lightManager(void);

//RTC clock
extern RTC_DS3231 rtc;

#endif