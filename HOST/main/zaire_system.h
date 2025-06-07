#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>


//POWER
#define HIGH        1
#define LOW         0

#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET // Bicycle Helmet specific logic

    //BUZZER
    #define BUZZER_INCLUDED
    #include "driver/ledc.h"
    #define BUZZER_FREQ_HZ      2000  // Default tone
    #define BUZZER_DUTY         4096  // Duty out of 8192 (50%)
    #define BUZZER_LEDC_CHANNEL LEDC_CHANNEL_0
    #define BUZZER GPIO_NUM_40
    void buzzer_init();
    void buzzer_off();
    void buzzer_on();
    void quick_buzz();
    void double_quick_buzz();

    //UART PASSING CODES
    #define WALKIE_PAIRING_MASTER     "P0"
    #define WALKIE_PAIRING_SLAVE      "P1"
    #define WALKIE_PAIRING_SYNC       "P2"
    #define WALKIE_PAIRING_COMPLETE   "P2"

    //AUDIO CHIP
    #if AUDIO_CHIP != AUDIO_CHIP_NONE
        #define AUDIO_PLAYER_NEXT     "B0"
        #define AUDIO_PLAYER_PREV     "B1"
        #define AUDIO_PLAYER_VOL_UP   "B2"
        #define AUDIO_PLAYER_VOL_DWN  "B3"
    #endif

    //BLINDSPOT
    #define BLINDSPOT_INCLUDED
    #include <esp_timer.h>
    #include "esp_rom_sys.h"
    #define BS_ECHO_RIGHT   GPIO_NUM_46
    #define BS_ECHO_LEFT    GPIO_NUM_45
    #define BS_TRIG_RIGHT   GPIO_NUM_48
    #define BS_TRIG_LEFT    GPIO_NUM_47
    #define BS_LED_RIGHT    GPIO_NUM_42
    #define BS_LED_LED      GPIO_NUM_41
    #define MAX_DISTANCE_CM       600  // Maximum measurable distance in cm
    #define MIN_DETECT_DISTANCE   -1 //ft - When the helmet alert rider of potential object (4 - motorcycle 2 bicycle) -- to be tested
    #define MAX_DETECT_DISTANCE   15 //ft - When the helmet does not alert rider of potential object (6 - motorcycle 4 bicycle) -- to be tested
    #define TIMEOUT_US            (MAX_DISTANCE_CM * 58) 
    extern int32_t  bs_rt_distance;
    extern int32_t  bs_lt_distance;
    void bs_monitor_init();
    int32_t bs_lt_get_distance(void);
    int32_t bs_rt_get_distance(void);
    
    #define LIGHTS_INCLUDED
    #include "led_strip.h"
    #define BACK_LED        GPIO_NUM_4
    #define FRONT_WHITE_LED GPIO_NUM_5
    #define FRONT_RED_LED   GPIO_NUM_11
    #define LED_STRIP_LED_NUMBERS 10
    #define LED_STRIP_RMT_RES_HZ  (10 * 1000 * 1000)
    #define AMBER_R 255
    #define AMBER_G 100
    #define AMBER_B 0
    typedef enum{
        NORMAL = 0,
        MASTER_PAIRING = 1,
        SLAVE_PAIRING = 2,
        SYNC_PAIRING = 3
    }led_target_stage_t;
    extern led_target_stage_t led_target_stage;
    typedef enum {
        LED_OFF = 0,
        FRONT_WHITE_ON = 1,
        LOW_BATTERY = 2,
        BACK_BRAKE_ON = 1,
        LEFT_TURN = 2,
        RIGHT_TURN = 3
    }led_target_mode_t;
    extern led_target_mode_t led_target_mode[2];
    led_strip_handle_t configure_led_stip();
    void led_welcome_animation(led_strip_handle_t led_strip);
    void led_front_white_on(void);
    void led_front_white_off(void);
    void led_battery_low_on(void);
    void led_battery_low_off(void);
    void led_right_turn(led_strip_handle_t led_strip);
    void led_left_turn(led_strip_handle_t led_strip);
    void led_brake_red(led_strip_handle_t led_strip);
    void led_pairing_master_search_blue(led_strip_handle_t led_strip);
    void led_pairing_slave_search_blue(led_strip_handle_t led_strip);
    void led_pairing_sync_blue(led_strip_handle_t led_strip);
    void led_pairing_complete(led_strip_handle_t led_strip);
    void led_off_all(led_strip_handle_t led_strip);

    #define DISPLAY_INCLUDED
    #include <u8g2.h>
    #include <u8g2_esp32_hal.h>
    #define DISPLAY_EN_PIN     GPIO_NUM_18
    #define DISPLAY_EN_BTN     GPIO_NUM_8
    #define CAMERA_ON_PIN      GPIO_NUM_14
    typedef enum {
        DISPLAY_EN_OFF = 0,
        DISPLAY_MAIN_UI = 1,
        DISPLAY_SHOW_LOW_BAT = 2,
        DISPLAY_SHOW_DNS_IP = 3,
    }display_target_t;
    extern display_target_t display_target;

    extern bool display_en; // Rather the display is on or not 
    extern u8g2_t display;
    esp_err_t display_init(void);
    void display_clear(void);
    void display_welcome_animation(void);
    void display_main_UI(void);
    void init_display_gpio(void);
    void display_power_on(void);
    void display_power_off(void);
        //DISPLAY ELEMENTS
        void display_datetime();
        void display_location();
        void display_elevation();
        void display_battery(uint8_t percent);
        void display_camera_icon(void);

        //PASSS
        void display_quick_show(void);
        //FULL SCREEN DISPLAY 
        void display_low_battery_warning(void);
        void display_dns_IP(void);
    
#elif DEVICE_TYPE == DEVICE_TYPE_SKI_GOGGLES
    // SKI Goggles-specific logic
    
    #define DISPLAY_INCLUDED
    #define DISPLAY_INCLUDED
    #include <u8g2.h>
    #include <u8g2_esp32_hal.h>
    #define DISPLAY_EN_PIN     GPIO_NUM_18
    #define DISPLAY_EN_BTN     GPIO_NUM_8
    #define CAMERA_ON_PIN      GPIO_NUM_14
    typedef enum {
        DISPLAY_EN_OFF = 0,
        DISPLAY_MAIN_UI = 1,
        DISPLAY_SHOW_LOW_BAT = 2,
        DISPLAY_SHOW_DNS_IP = 3,
    }display_target_t;
    extern display_target_t display_target;

    extern bool display_en; // Rather the display is on or not 
    extern u8g2_t display;
    esp_err_t display_init(void);
    void display_clear(void);
    void display_welcome_animation(void);
    void display_main_UI(void);
    void init_display_gpio(void);
    void display_power_on(void);
    void display_power_off(void);
        //DISPLAY ELEMENTS
        void display_datetime();
        void display_location();
        void display_elevation();
        void display_battery(uint8_t percent);
        void display_camera_icon(void);

        //PASSS
        void display_quick_show(void);
        //FULL SCREEN DISPLAY 
        void display_low_battery_warning(void);
        void display_dns_IP(void);

#elif DEVICE_TYPE == DEVICE_TYPE_MOTOR_HELMET
    // Motor Helmet specific logic
    //BLINDSPOT
    #define BLINDSPOT_INCLUDED
    #define BS_ECHO_RIGHT   GPIO_NUM_46
    #define BS_ECHO_LEFT    GPIO_NUM_45
    #define BS_TRIG_RIGHT   GPIO_NUM_48
    #define BS_TRIG_LEFT    GPIO_NUM_47
    #define BS_LED_RIGHT    GPIO_NUM_42
    #define BS_LED_LED      GPIO_NUM_41
    esp_err_t blindspot_init();
   
    #define DISPLAY_INCLUDED
    #define DISPLAY_INCLUDED
    #include <u8g2.h>
    #include <u8g2_esp32_hal.h>
    #define DISPLAY_EN_PIN     GPIO_NUM_18
    #define DISPLAY_EN_BTN     GPIO_NUM_8
    #define CAMERA_ON_PIN      GPIO_NUM_14
    typedef enum {
        DISPLAY_EN_OFF = 0,
        DISPLAY_MAIN_UI = 1,
        DISPLAY_SHOW_LOW_BAT = 2,
        DISPLAY_SHOW_DNS_IP = 3,
    }display_target_t;
    extern display_target_t display_target;

    extern bool display_en; // Rather the display is on or not 
    extern u8g2_t display;
    esp_err_t display_init(void);
    void display_clear(void);
    void display_welcome_animation(void);
    void display_main_UI(void);
    void init_display_gpio(void);
    void display_power_on(void);
    void display_power_off(void);
        //DISPLAY ELEMENTS
        void display_datetime();
        void display_location();
        void display_elevation();
        void display_battery(uint8_t percent);
        void display_camera_icon(void);

        //PASSS
        void display_quick_show(void);
        //FULL SCREEN DISPLAY 
        void display_low_battery_warning(void);
        void display_dns_IP(void);

#elif DEVICE_TYPE == DEVICE_TYPE_TEST

#else
   #error "Unknown DEVICE_TYPE defined" // Defaults at 0
#endif



//File Management
esp_err_t init_spiffs(void);

//System
esp_err_t zaire_system_check();
esp_err_t zaire_load_nvs_data();


#endif // ZAIRE_SYSTEM_H
