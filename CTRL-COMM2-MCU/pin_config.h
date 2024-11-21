#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

//Camera Pin Configuration
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    15
#define SIOD_GPIO_NUM     4
#define SIOC_GPIO_NUM     5

#define Y9_GPIO_NUM      16
#define Y8_GPIO_NUM      17
#define Y7_GPIO_NUM      18
#define Y6_GPIO_NUM      12
#define Y5_GPIO_NUM      10
#define Y4_GPIO_NUM       8
#define Y3_GPIO_NUM       9
#define Y2_GPIO_NUM      11

#define VSYNC_GPIO_NUM    6
#define HREF_GPIO_NUM     7
#define PCLK_GPIO_NUM    13

// SD Card Pin Configuration
#define SD_MMC_CMD       38
#define SD_MMC_CLK       39
#define SD_MMC_D0        40

//COMM2
#define COMM2_BCK        33
#define COMM2_WS         36
#define COMM2_DIN        14
#define COMM2_DOUT       34
//Buttons and LEDs
#define PURPOSE_BTN      1
#define PURPOSE_LED      46

//BUZZER
#define BUZZER           45
#define BUZZER_CHANNEL   0

//SIGNALS
#define WALKIE_PIN       47
#define POWER_SIGNAL     35 // LOW -> ON -- HIGH -> OFF

//UART 
#define SERIAL_WALKIE_RX 2
#define SERIAL_WALKIE_TX 3
#define SERIAL_BT_RX     20
#define SERIAL_BT_TX     19

//IMPACT DEVICE
#define IMPACT_TOP_PIN   37
#define IMPACT_LEFT_PIN  41
#define IMPACT_RIGHT_PIN 42
 
//I2S
#define I2C_SCL          2
#define I2C_SDA          3

//ACCESS
#define FAN_PIN          21


#endif 