#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>


//POWER
#define HIGH        1
#define LOW         0



#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET
    // Bicycle Helmet specific logic
    //BLINDSPOT
    #define BLINDSPOT_INCLUDED
    #define BS_ECHO_RIGHT   GPIO_NUM_46
    #define BS_ECHO_LEFT    GPIO_NUM_45
    #define BS_TRIG_RIGHT   GPIO_NUM_48
    #define BS_TRIG_LEFT    GPIO_NUM_47
    #define BS_LED_RIGHT    GPIO_NUM_42
    #define BS_LED_LED      GPIO_NUM_41
    esp_err_t blindspot_init();
   
    #define DISPLAY_INCLUDED
    
#elif DEVICE_TYPE == DEVICE_TYPE_SKI_GOGGLES
    // SKI Goggles-specific logic
    
    #define DISPLAY_INCLUDED

#elif DEVICE_TYPE == DEVICE_TYPE_MOTOR_HELMET
    // Motor Helmet specific logic
    //BLINDSPOT
    #define BLINDSPOT_INCLUDED
    #define BS_ECHO_RIGHT   GPIO_NUM_46
    #define BS_ECHO_LEFT    GPIO_NUM_45
    #define BS_TRIG_RIGHT   GPIO_NUM_48
    #define BS_TRIG_LEFT    GPIO_NUM_47
    #define BS_LED_RIGHT    GPIO_NUM_42
    #define BS_LED_LED      GPIO_NUM_41
    esp_err_t blindspot_init();
   
    #define DISPLAY_INCLUDED
#else
    #error "Unknown DEVICE_TYPE defined" // Defaults at 0
#endif


//File Management
esp_err_t init_spiffs(void);


//System
esp_err_t zaire_system_check();
esp_err_t zaire_load_nvs_data();

#endif // ZAIRE_SYSTEM_H
