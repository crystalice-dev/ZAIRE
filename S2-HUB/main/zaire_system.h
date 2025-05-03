#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>

//DEVICE TYPES
#define DEVICE_TYPE_BICYCLE_HELMET  (0)
#define DEVICE_TYPE_SKI_GOGGLES     (1)
#define DEVICE_TYPE_MOTOR_HELMET    (2)



#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET
    // Bicycle Helmet specific logic
    #define DEVICE_NAME "ZAIRE BIKE VISION"
    

#elif DEVICE_TYPE == DEVICE_TYPE_SKI_GOGGLES
    // SKI Goggles-specific logic
    #define DEVICE_NAME "ZAIRE SKI VISION"
    #define DISPLAY_INCLUDED

#elif DEVICE_TYPE == DEVICE_TYPE_MOTOR_HELMET
    // Motor Helmet specific logic
    #define DEVICE_NAME "ZAIRE MOTOR VISION"

#else
    #error "Unknown DEVICE_TYPE defined" // Defaults at 0
#endif


//From EEPROM
uint8_t get_device_type(void);
esp_err_t set_device_type(uint8_t device_n);

#endif // ZAIRE_SYSTEM_H
