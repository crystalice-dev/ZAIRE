#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H
#include "globalVar.h"


#define SUMMIT      0x01
#define SUMMIT_PRO  0x02
#define RIDGE       0x03

#define ZAIRE_OK    ESP_OK
#define ZAIRE_FAIL  ESP_FAIL
#define HIGH        0x01
#define LOW         0x00
esp_err_t zaire_system_init();
void zaire_reset_all_pins();

//<-------------- SYSTEM CALLS--------------->//
#define SHORT_PRESS_DELAY   250
#define LONG_PRESS_DELAY    1500
extern bool is_esp_now_active;
extern int is_setting_on;
extern bool is_walkie_on;
extern bool is_walkie_mute;
extern uint8_t current_BT_vol;
extern int top_speed_gps;

typedef enum{
    NONE = 0,
    MASTER = 1,
    SLAVE = 2,
    SYNC = 3
}walkie_pairing_mode_t;
extern walkie_pairing_mode_t walkie_pairing_mode;
extern bool is_walkie_in_pairing_session;
esp_err_t init_spiffs(void); // spiffs
//<------------------- END ------------------>//

#define WALKIE_BTN      GPIO_NUM_21
#define PURPOSE_LEFT    GPIO_NUM_45
#define PURPOSE_RIGHT   GPIO_NUM_48


typedef enum {
    DISPLAY_EN_OFF = 0,
    DISPLAY_MAIN_UI = 1,
    DISPLAY_SHOW_LOW_BAT = 2,
    DISPLAY_SHOW_DNS_SETTING = 3,
    DISPLAY_SHOW_WALKIE_SETTING = 4,
    DISPLAY_SHOW_WALKIE_MASTER_SETTING = 5,
    DISPLAY_SHOW_WALKIE_SLAVE_SETTING = 6,
    DISPLAY_SHOW_WALKIE_SYNC_SETTING = 7,
    DISPLAY_SHOW_WALKIE_PAIRED_SETTING = 8,
    DISPLAY_SHOW_WALKIE_CANCELED_SETTING = 9,
    DISPLAY_SHOW_WALKIE_MASTER_SEARCH_SETTING = 10,
    DISPLAY_SHOW_WALKIE_SLAVE_SEARCH_SETTING = 11,
    DISPLAY_SHOW_WALKIE_MUTE_SEQUENCE = 12,
    DISPLAY_SHOW_WALKIE_DELETE_SEQUENCE = 13,
    DISPLAY_SHOW_WALKIE_ENTER_PAIRING_SEQUENCE = 14,
    DISPLAY_SHOW_BK3266_BLUETOOTH = 15,
    DISPLAY_SHOW_BK3266_BLUETOOTH_PWR_SEQUENCE = 16,
    DISPLAY_SHOW_SYSTEM_RESTART = 17
}display_target_t;
extern display_target_t display_target;

typedef enum{
    DISPLAY_OFF = 0,
    DISPLAY_MAIN = 1,
    DISPLAY_SETTINGS = 2,
    DISPLAY_BLUETOOTH = 3,
    DISPLAY_WALKIE_HOST = 4,
    DISPLAY_WALKIE_RCVR = 5,
    DISPLAY_SYSTEM_RESTART = 6
}display_button_target_t;

extern display_button_target_t display_button_target;


//<-------------- USER SETTINGS--------------->//

typedef struct {
    char user_name[64];
    char device_name[256];
    char device_lang[4]; // "ar", "en", "es", "fr", "de", "it", "jp", "kr", "ru", "cn"
    char device_units[2]; // 1 = imperial, 0 = metric
    char device_color_theme[2]; // 1 = dark, 0 = light
    char device_auto_record[2]; // 1 = on, 0 = off -- tart recording when > ~5 km/h
    char device_mute_record_audio[2]; // 1 = on, 0 = off -- does not record audio with video
    char device_lower_bt_volume_on_walkie[2]; // 1 = on, 0 = off -- lower bt volume when communicating on walkie
    char device_auto_bt_enable_on_powerup[2]; // 1 = on, 0 = off -- enable bluetooth on power up

}user_settings_t;

extern user_settings_t user_settings;


#endif