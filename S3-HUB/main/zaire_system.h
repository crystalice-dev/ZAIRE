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

#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET // Bicycle Helmet specific logic
    //UART PASSING CODES
    #define WALKIE_PAIRING_MASTER     "P0"
    #define WALKIE_PAIRING_SLAVE      "P1"
    #define WALKIE_PAIRING_SYNC       "P2"
    #define WALKIE_PAIRING_COMPLETE   "P3"

    #if AUDIO_CHIP != AUDIO_CHIP_NONE
        #define AUDIO_PLAYER_TARGET         'B'
        #define AUDIO_PLAYER_TARGET_NAME    ':' // Change name
        #define AUDIO_PLAYER_NEXT           0x00
        #define AUDIO_PLAYER_PREV           0x01
        #define AUDIO_PLAYER_VOL_UP         0x02
        #define AUDIO_PLAYER_VOL_DWN        0x03
        void audio_chip_uart_handler(uint8_t code);
    #endif

    #if AUDIO_CHIP == AUDIO_CHIP_BK3266
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
        void bk_init(void);
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

    //WALKIE
    #define DEVICE_PAIRING_NAME         "zairehelmetsPairing_0" 
    #define ESP_NOW_CHANNEL             1
    #define DEFAULT_SCAN_LIST_SIZE      10
    #define WALKIE_BTN                  GPIO_NUM_46
    #define WALKIE_NEW_MESH             0xF5
    #define WALKIE_PAIRING_DONE     0xA2
    typedef enum{
        NONE = 0,
        MASTER = 1,
        SLAVE = 2,
        SYNC = 3
    }walkie_pairing_mode_t;
    extern walkie_pairing_mode_t walkie_pairing_mode;
    extern bool mesh_system_active;
    extern uint8_t device_sta_mac[6];
    extern uint8_t peer_addresses[8][6];
    extern uint8_t temp_peer_addr[6];
    extern uint8_t number_paired_peers;
    extern bool sendOver;
    extern bool recOver;
    extern bool speakOut;
    extern int32_t *samples_32bit;
    extern int16_t *samples_16bit;
    extern uint8_t *samples_8bit ;
    extern int16_t *recive_16bit;
    extern int16_t *output_16bit;
    esp_err_t init_i2s(void);
    int init_i2s_read(int16_t *samples, int count);
    esp_err_t init_wifi(void);
    esp_err_t station_reconfig(void);
    esp_err_t master_reconfig(void);
    esp_err_t slave_reconfig(void);
    esp_err_t init_esp_now(void);
    void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
    void esp_now_recv_cb(const uint8_t *mac_addr,  const uint8_t *data, int data_len);
    void walkie_discover_peers(void);
    void walkie_discoverable_peer(void);
    esp_err_t add_peer_to_mesh(uint8_t *addr);
    esp_err_t remove_peer_from_mesh(uint8_t *addr);
    void walkie_pairing_master(void);
    void walkie_pairing_slave(void);
    void walkie_pairing_sync(uint8_t *addr);
    void walkie_pairing_max(uint8_t *addr);
    void walkie_pairing_new_mesh(uint8_t *addr);
    
#elif DEVICE_TYPE == DEVICE_TYPE_SKI_GOGGLES // SKI Goggles-specific logic
    
    #define DISPLAY_INCLUDED

#elif DEVICE_TYPE == DEVICE_TYPE_MOTOR_HELMET // Motor Helmet specific logic
    
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
