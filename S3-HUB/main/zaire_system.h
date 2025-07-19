#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>


//POWER
#define HIGH        1
#define LOW         0

//SYSTEM
#define OPENED                      (1)
#define CLOSED                      (0)
#define mesh_system_max_connection  (10)

#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET // Bicycle Helmet specific logic
   
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
    #define WALKIE_INCLUDED
    #include <driver/i2s.h>
    #define WALKIE_PAIRING_MASTER     "P0"
    #define WALKIE_PAIRING_SLAVE      "P1"
    #define WALKIE_PAIRING_SYNC       "P2"
    #define WALKIE_PAIRING_COMPLETE   "P3"
    #define WALKIE_MUTE_ON            "B1"
    #define WALKIE_MUTE_OFF           "B0"
    #define DEVICE_PAIRING_NAME         "zairehelmetsPairing_0" 
    #define ESP_NOW_CHANNEL             1
    #define DEFAULT_SCAN_LIST_SIZE      10
    #define WALKIE_BTN                  GPIO_NUM_46
    #define WALKIE_BCK                  GPIO_NUM_1
    #define WALKIE_WS                   GPIO_NUM_2
    #define WALKIE_DIN                  GPIO_NUM_3
    #define WALKIE_DOUT                 GPIO_NUM_14
    #define SAMPLE_RATE                 15500 //15500
    #define WALKIE_REQUEST_STA_MAC      0xB1
    #define WALKIE_NEW_MESH             0xF5
    #define WALKIE_PAIRING_DONE         0xA2
    typedef enum{
        NONE = 0,
        MASTER = 1,
        SLAVE = 2,
        SYNC = 3
    }walkie_pairing_mode_t;
    extern walkie_pairing_mode_t walkie_pairing_mode;
    extern uint8_t device_sta_mac[6];
    extern uint8_t peer_addresses[8][6];
    extern uint8_t temp_peer_addr[6];
    extern uint8_t number_paired_peers;
    extern uint8_t new_peers;
    extern bool mesh_system_active;
    extern bool sendOver;
    extern bool recOver;
    extern bool speakOut;
    extern bool walkie_mute;
    extern int32_t *samples_32bit;
    extern int16_t *samples_16bit;
    extern uint8_t *samples_8bit ;
    extern int16_t *recive_16bit;
    extern int16_t *output_16bit;
    extern const i2s_port_t REC_I2S_PORT;
    extern const i2s_port_t SPK_I2S_PORT;
    void I2SInit();
    int I2Sread(int16_t *samples, int count);
    void covert_bit(int16_t *temp_samples_16bit,uint8_t*temp_samples_8bit,uint8_t len );
    void I2Swrite(int16_t *samples, int count);
    esp_err_t init_wifi(void);
    esp_err_t station_reconfig(void);
    esp_err_t master_reconfig(void);
    esp_err_t slave_reconfig(void);
    esp_err_t init_esp_now(void);
    void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
    esp_now_recv_cb_t esp_now_recv_cb(const uint8_t *mac_addr,  const uint8_t *data, int data_len);
    void walkie_snt(const uint8_t *i2s_data, uint16_t i2s_len);
    void walkie_rcvd(uint16_t i2s_data);
    void walkie_discover_peers(void);
    void request_sta_mac_addr(uint8_t *addr);
    esp_err_t remove_peer_from_mesh(uint8_t *addr);
    void walkie_pairing_master(void);
    void walkie_pairing_slave(void);
    void walkie_pairing_sync(uint8_t *addr);
    void walkie_pairing_max(uint8_t *addr);
    void walkie_pairing_new_mesh(uint8_t *addr);

    //USB-CAM
    #define PWDN_GPIO_NUM               (-1)
    #define RESET_GPIO_NUM              (-1)
    #define XCLK_GPIO_NUM               GPIO_NUM_15
    #define SIOD_GPIO_NUM               GPIO_NUM_4
    #define SIOC_GPIO_NUM               GPIO_NUM_5

    #define Y9_GPIO_NUM                 GPIO_NUM_16
    #define Y8_GPIO_NUM                 GPIO_NUM_17
    #define Y7_GPIO_NUM                 GPIO_NUM_18
    #define Y6_GPIO_NUM                 GPIO_NUM_12
    #define Y5_GPIO_NUM                 GPIO_NUM_10
    #define Y4_GPIO_NUM                 GPIO_NUM_8
    #define Y3_GPIO_NUM                 GPIO_NUM_9 // 1
    #define Y2_GPIO_NUM                 GPIO_NUM_11 //0

    #define VSYNC_GPIO_NUM              GPIO_NUM_6
    #define HREF_GPIO_NUM               GPIO_NUM_7
    #define PCLK_GPIO_NUM               GPIO_NUM_13
    #define UVC_MAX_FRAMESIZE_SIZE      (60*1024)
    esp_err_t usb_init(void);
    esp_err_t camera_init(void);
    uvc_fb_t* camera_fb_get_cb(void *cb_ctx);
    void camera_fb_return_cb(uvc_fb_t *fb, void *cb_ctx);
    void camera_stop_cb(void *cb_ctx);
    esp_err_t camera_start_cb(uvc_format_t format, int width, int height, int rate, void *cb_ctx);
    
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
