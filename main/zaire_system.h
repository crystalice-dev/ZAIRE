#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H
#include "globlaVar.h"


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

typedef enum{
    NONE = 0,
    MASTER = 1,
    SLAVE = 2,
    SYNC = 3
}walkie_pairing_mode_t;
extern walkie_pairing_mode_t walkie_pairing_mode;

esp_err_t init_spiffs(void); // spiffs
//<------------------- END ------------------>//

#define WALKIE_BTN      GPIO_NUM_21
#define PURPOSE_LEFT    GPIO_NUM_45
#define PURPOSE_RIGHT   GPIO_NUM_48
#define BK3266_PP_CALL  GPIO_NUM_46

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
    DISPLAY_SHOW_WALKIE_ENTER_PAIRING_SEQUENCE = 14
}display_target_t;
extern display_target_t display_target;

#if TIER == SUMMIT

    //Mass Storate
    #define W25Q128

#elif TIER == SUMMIT_PRO

#elif TIER == RIDGE

#endif

#endif