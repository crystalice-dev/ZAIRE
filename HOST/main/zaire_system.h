#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>


//POWER
#define HIGH        1
#define LOW         0



#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET
    // Bicycle Helmet specific logic
   
    #define DISPLAY_INCLUDED
    
#elif DEVICE_TYPE == DEVICE_TYPE_SKI_GOGGLES
    // SKI Goggles-specific logic
    
    #define DISPLAY_INCLUDED

#elif DEVICE_TYPE == DEVICE_TYPE_MOTOR_HELMET
    // Motor Helmet specific logic
    
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
