#ifndef ZAIRE_SYSTEM_H
#define ZAIRE_SYSTEM_H

#include <globalVar.h>


//POWER
#define HIGH        1
#define LOW         0



#if DEVICE_TYPE == DEVICE_TYPE_BICYCLE_HELMET
    // Bicycle Helmet specific logic
    //BLINDSPOT
    #define BLINDSPOT_INCLUDED
    #define BS_ECHO_RIGHT   GPIO_NUM_46
    #define BS_ECHO_LEFT    GPIO_NUM_45
    #define BS_TRIG_RIGHT   GPIO_NUM_48
    #define BS_TRIG_LEFT    GPIO_NUM_47
    #define BS_LED_RIGHT    GPIO_NUM_42
    #define BS_LED_LED      GPIO_NUM_41
    esp_err_t blindspot_init();
   
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
    led_strip_handle_t configure_led_stip();
    void play_right_turn(led_strip_handle_t led_strip);
    void play_left_turn(led_strip_handle_t led_strip);
    void play_brake_red(led_strip_handle_t led_strip);
    void turn_off_all(led_strip_handle_t led_strip);

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

#else
    #error "Unknown DEVICE_TYPE defined" // Defaults at 0
#endif


//File Management
esp_err_t init_spiffs(void);


//System
esp_err_t zaire_system_check();
esp_err_t zaire_load_nvs_data();

#endif // ZAIRE_SYSTEM_H
