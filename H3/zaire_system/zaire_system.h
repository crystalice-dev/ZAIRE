#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H
#include "globalVar.h"


#define HIGH                    1
#define LOW                     0
#define ZAIRE_OK                0
#define ZAIRE_FAIL              -1

//System
#define ESP_RST                 29
#define ESP_BOOT0               28
#define CAMERA_EN               27
#define ON_BOARD_LED            26
int zaire_system_setup();

//First
typedef enum {
	NONE     =  0x00,
        STANDBY  =  0x01,
        FLASHING =  0x02
} onBoardLED_t;
extern onBoardLED_t onBoardLED;
extern uint8_t isFirstBoot;
int flash_ESP_FIRMWARE(void);
void flash_RST_ESP(void);
void flash_BOOT_ESP(void);
void flash_FLASH_ESP_HOST_FIRMWARE(void);
void flash_FLASH_ESP_WALKIE_FIRMWARE(void);

#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET
    // Bicycle Helmet specific logic
    #define DISPLAY_INCLUDED
    #define CAMERA_INCLUDED
    
#elif DEVICE_TYPE == DEVICE_TYPE_SKI_GOGGLES
    // SKI Goggles-specific logic
    
    #define DISPLAY_INCLUDED

#elif DEVICE_TYPE == DEVICE_TYPE_MOTOR_HELMET
    // Motor Helmet specific logic
    
    #define DISPLAY_INCLUDED

#else
    #error "Unknown DEVICE_TYPE defined" // Defaults at 0
#endif

#endif
