#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>


//POWER
#define HIGH        1
#define LOW         0

//SYSTEM
#define OPENED                      (1)
#define CLOSED                      (0)
#define ESP_NOW_CHANNEL             (3)
#define mesh_system_max_connection  (10)
typedef enum {
    NONE = 0,
    BK3266 = 0x01
}audio_chip_system_t;
#define AUDIO_CHIP BK3266

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


#if AUDIO_CHIP == BK3266
    //BK3266
    #define BK_GET_MAC_CMD              "AT+MAC\r\n"
    #define BK_GET_NAME                 "AT+NAME\r\n"
    #define BK_NEXT_SONG                "AT+NEXT\r\n"
    #define BK_PREV_SONG                "AT+LAST\r\n"
    #define BK_GET_CONNECTION_STATUS    "AT+STAT\r\n"
    #define BK_GET_PLAYER_STATUS        "AT+PSTAT\r\n"
    #define BK_LAST_CALL                "AT+CALL\r\n"
    #define BK_DISCONNECT               "AT+DISC\r\n"
    #define BK_EN_PHONE                 "AT+CALEN1\r\n"
    #define BK_DIS_PHONE                "AT+CALEN0\r\n"
    #define BK_NOTIFICATION             "AT+VOICE10\r\n"
    typedef enum {
        NORMAL   = 0,
        GET_NAME = 1,
        SET_NAME = 2,
        SET_VOL  = 3,
        SET_SONG = 4,
        GET_P_STATUS = 5, //PLAYER
        GET_C_STATUS = 6, //CONNECTION
        DISCONNECT = 7
    }bk_target_stage_t;

    typedef enum {
        DISCONNECTED = 0,
        CONNECTED = 1
    }bk_connection_mode_t;

    extern bk_target_stage_t bk_target_stage;
    extern bk_connection_mode_t bk_connection_mode;
    extern uint8_t bk_volume;
    void bk_set_device_name(const char *name);
    void bk_get_device_name(void);
    void bk_set_device_volume(uint8_t vol);
    void bk_get_player_status(void);
    void bk_get_connection_status(void);
    void bk_vol_up(void);
    void bk_vol_down(void);
    void bk_next_song(void);
    void bk_prev_song(void);
    void bk_key(void); // Play - Pause - Answer call - Decline call
    void bk_disconnect(void);
    void bk_phone_en(void);
    void bk_notification(void);
#endif

#endif // ZAIRE_SYSTEM_H
