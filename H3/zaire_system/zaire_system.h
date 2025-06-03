#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H
#include "globalVar.h"


#define HIGH                    1
#define LOW                     0
#define ZAIRE_OK                0
#define ZAIRE_FAIL              -1

//System
#define HOST_BOOT0              27
#define WALKIE_BOOT0            28
#define CAMERA_EN               29

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

#endif