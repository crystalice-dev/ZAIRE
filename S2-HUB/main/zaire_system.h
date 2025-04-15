#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>

//DEVICE TYPES
#define DEVICE_TYPE_BICYCLE_HELMET  (0)
#define DEVICE_TYPE_SKI_GOGGLES     (1)
#define DEVICE_TYPE_MOTOR_HELMET    (2)


#ifndef DEVICE_TYPE
    #define DEVICE_TYPE DEVICE_TYPE_SKI_GOGGLES
#endif


#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET
    // Bicycle Helmet specific logic
    #define DEVICE_NAME "ZAIRE BICYCLE VISION"

#elif DEVICE_TYPE == DEVICE_TYPE_SKI_GOGGLES
    // SKI Goggles-specific logic
    #define DEVICE_NAME "ZAIRE SKI VISION"

#elif DEVICE_TYPE == DEVICE_TYPE_MOTOR_HELMET
    // Motor Helmet specific logic
    #define DEVICE_NAME "ZAIRE MOTOR HELMET"

#else
    #error "Unknown DEVICE_TYPE defined"
#endif

#endif // ZAIRE_SYSTEM_H
