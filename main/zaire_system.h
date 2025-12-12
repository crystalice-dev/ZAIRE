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


// ======================
// 1. USER SETTINGS (stored in NVS, survives reboot)
// ======================
typedef struct {
    char user_name[64];      // "Alex", "ZAIRE Rider", etc.
    char device_name[64];    // "ZAIRE-VISION-001", "SnowBeast"
} user_prefs_t;

// ======================
// 2. SYSTEM SETTINGS (user preferences, stored in NVS)
// ======================
typedef struct {
    uint8_t device_lang;            // 0 = English, 1 = French, etc.
    uint8_t units;                    // 0 = metric (km/h, m), 1 = imperial (mph, ft)
    uint8_t theme;                   // 0 = light, 1 = dark
    uint8_t lower_bt_volume_on_walkie;// 0 = no, 1 = yes
    uint8_t auto_bt_on_powerup;       // 0 = off, 1 = on
    uint8_t device_auto_record;      // 0 = off, 1 = on
    uint8_t device_mute_record_audio; // 0 = off, 1 = on
    // Add more user prefs here later (vibration, HUD brightness, etc.)
} system_prefs_t;

// ======================
// 3. DEVICE STATE (live/runtime data, NOT saved to flash)
// ======================
typedef struct {
    uint16_t photos_count;            // current number of photos in /media/photos/
    uint8_t  walkie_peers_count;       // how many walkie helmets/goggles are connected
    bool     bt_connected;            // is Bluetooth currently linked?
    bool     bt_audio_active;         // is audio streaming?
    char     bt_device_name[64];      // "Alex’s iPhone",
    bool     walkie_active;           // is walkie-talkie session running?
    bool     walkie_paired;           // has at least one peer been paired ever?
    float    top_speed;               // current session best (in current units)
    uint16_t top_height;              // meters or feet
    float    top_accel;               // ft/s or m/s²
    char     last_photo_time[6];      // "14:32"
    // Add live sensors here: battery %, temperature, GPS fix, etc.
} device_state_t;

// ======================
// 4. WALKIE PEER INFO STRUCTURE AND GLOBAL ARRAY
// ======================

typedef struct {
    uint8_t  id;                        // 0–8 → matches array index
    char     name[32];                  // "Alex", "Helmet #5"
    char     last_position[64];         // "Ridge lookout", "GPS: 46.8123,-121.7456"
    uint32_t last_comm_timestamp;       // Unix timestamp (seconds since 1970)
    int16_t  rssi;                      // signed! RSSI is always negative (-30 to -100)
    uint8_t  battery_level;             // 0–100%
    uint8_t  __padding[1];              // align to 128 bytes (nice for flash/JSON)
} walkie_peer_zState_t;

// ======================
// Global instances
// ======================
extern user_prefs_t    g_user_prefs;
extern system_prefs_t  g_system_prefs;
extern device_state_t  g_device_state;

#endif