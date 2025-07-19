#include "globalVar.h"



TaskHandle_t gpio_purpose_btn_task_handler = NULL;
TaskHandle_t gpio_walkie_btn_task_handler = NULL;
TaskHandle_t gps_uart_task_handler = NULL;
TaskHandle_t h3_uart_task_handler = NULL;
TaskHandle_t walkie_uart_task_handler = NULL;
TaskHandle_t i2c_task_handler = NULL;
TaskHandle_t display_task_handler = NULL;
TaskHandle_t led_strip_task_handler = NULL;
TaskHandle_t display_camera_btn_task_handler = NULL;
TaskHandle_t bs_left_monitor_handler = NULL;
TaskHandle_t bs_right_monitor_handler = NULL;
TaskHandle_t walkie_task_handler = NULL;


void gpio_purpose_run_task(void *vpParam){

    #ifdef REMOTE_INCLUDED
        //Check if remote pairing is requested
        if(gpio_get_level(PURPOSE_BTN) == HIGH){
            led_target_stage = REMOTE_PAIRING;
            demo_mode = false;
            vTaskDelay(pdMS_TO_TICKS(4000));
        }
    #endif



    while(demo_mode){
        if(gpio_get_level(PURPOSE_BTN)){
            demo_mode = false;
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    while (1)
    {

        if(gpio_get_level(PURPOSE_BTN) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
            vTaskDelay(pdMS_TO_TICKS(250));
            if(gpio_get_level(PURPOSE_BTN) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
                display_target = DISPLAY_SHOW_DNS_SETTING;
                quick_buzz();
            }
        }else{
            vTaskDelay(pdMS_TO_TICKS(2000));
            if(gpio_get_level(PURPOSE_BTN) == HIGH && gpio_get_level(WALKIE_BTN) == HIGH){
                led_target_stage = BLUETOOTH_PAIRING;
                printf("BLUETOOTH\n");
                double_quick_buzz();
                display_target = DISPLAY_SHOW_BLUETOOTH_PAIRING;
                vTaskDelay(pdMS_TO_TICKS(3000));
                led_target_stage = NORMAL;
                display_target = DISPLAY_MAIN_UI;
                quick_buzz();
            }
        }

        
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    

}

void gpio_walkie_run_task(void *vpParam){

    while (demo_mode)
    {
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    
    while (1)
    {
        if(gpio_get_level(WALKIE_BTN) == HIGH && gpio_get_level(PURPOSE_BTN) == LOW){
            vTaskDelay(pdMS_TO_TICKS(500));
            if(gpio_get_level(WALKIE_BTN) == HIGH && walkie_paired && gpio_get_level(PURPOSE_BTN) == LOW){
                sendOver = 1;
            }else{
                vTaskDelay(pdMS_TO_TICKS(2000));
                if(gpio_get_level(WALKIE_BTN) == HIGH && gpio_get_level(PURPOSE_BTN) == HIGH){
                    led_target_stage = MASTER_PAIRING;
                    printf("master\n");
                    quick_buzz();
                    vTaskDelay(pdMS_TO_TICKS(2000));
                    
                    if(gpio_get_level(WALKIE_BTN) == HIGH){
                        led_target_stage = SLAVE_PAIRING;
                        double_quick_buzz();
                        vTaskDelay(pdMS_TO_TICKS(2000));
                        
                        if(gpio_get_level(WALKIE_BTN) == HIGH){
                            led_target_stage = NONE;
                        }else{
                            walkie_pairing_mode = SLAVE;
                           //walkie_pairing_slave();
                            display_target = DISPLAY_SHOW_WALKIE_PAIRING;

                        }
                    }else{
                        walkie_pairing_mode = MASTER;
                        display_target = DISPLAY_SHOW_WALKIE_PAIRING;
                        double_quick_buzz();
                        walkie_pairing_master();
                        
                    }
                }
            }
        }else{
            sendOver = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    

}

#ifdef LIGHTS_INCLUDED
    void led_strip_run_task(void *vpParam){

        led_strip_handle_t led_strip = configure_led_stip();
        led_welcome_animation(led_strip);
        while(demo_mode){
            led_demo_operation(led_strip);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        while (1)
        {
            switch (led_target_mode[0]){
                case LED_OFF:
                    led_front_white_off();
                    break;
                
                case FRONT_WHITE_ON:
                    led_front_white_on();
                    break;

                case FRONT_WHITE_PWM:
                    

                case LOW_BATTERY:
                    led_battery_low_on();
                default:
                    break;
            }

            switch (led_target_stage){
                case NORMAL:
                    switch (led_target_mode[1]){
                        case LED_OFF:
                            led_off_all(led_strip);
                            break;
                        
                        case BACK_BRAKE_ON:
                            led_brake_red(led_strip);
                            break;
                        
                        case LEFT_TURN:
                            led_left_turn(led_strip);
                            break;

                        case RIGHT_TURN:
                            led_right_turn(led_strip);
                            break;

                        default:
                            break;
                    }
                    break;
                
                case MASTER_PAIRING:
                    led_pairing_master_search_blue(led_strip);
                    break;
                case SLAVE_PAIRING:
                    led_pairing_slave_search_blue(led_strip);
                    break;
                case SYNC_PAIRING:
                    led_pairing_sync_blue(led_strip);
                    break;
                case REMOTE_PAIRING:
                    led_pairing_remote(led_strip);
                    break;
                case BLUETOOTH_PAIRING:
                    led_pairing_bluetooth(led_strip);
                    break;
                default:
                    break;
            }

            vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
        }
        
    }
#endif

#ifdef BLINDSPOT_INCLUDED


    void bs_left_monitor_task(void *vpParam){

        while (demo_mode)
        {

            for (uint8_t i = 0; i < 255; i+=15) {
                set_BS_led_brightness(i, i);
                vTaskDelay(pdMS_TO_TICKS(100));
            }

            // Use int to safely reach 0 without wraparound
            for (int i = 255; i >= 0; i-=15) {
                set_BS_led_brightness(i, i);
                vTaskDelay(pdMS_TO_TICKS(100));
            }

            vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
        }

        while (1){
            int32_t distance = bs_lt_get_distance();

            if(distance  < 25 && distance > 5){
                vTaskDelay(pdMS_TO_TICKS(100));
                distance = bs_lt_get_distance();
                
                if(distance < 25 && distance > 5){
                    for (uint8_t i = 0; i < 255; i+=15) {
                        set_BS_led_left(i);
                        vTaskDelay(pdMS_TO_TICKS(25));
                    }
                    while (1)
                    {
                        vTaskDelay(pdMS_TO_TICKS(3000));
                        distance = bs_lt_get_distance();
                        if(distance > 25)break;
                    }
                    for (int i = 255; i >= 0; i-=15) {
                        set_BS_led_left(i);
                        vTaskDelay(pdMS_TO_TICKS(25));
                    }

                    
                }            
            }
            
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }

    void bs_right_monitor_task(void *vpParam){

        while (demo_mode)
        {
            vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
        }

        while (1){
            int32_t distance = bs_rt_get_distance();
       

            if(distance  < 25 && distance > 5){
                vTaskDelay(pdMS_TO_TICKS(100));
                distance = bs_rt_get_distance();
                
                if(distance < 25 && distance > 5){
                    for (uint8_t i = 0; i < 255; i+=15) {
                        set_BS_led_right(i);
                        vTaskDelay(pdMS_TO_TICKS(25));
                    }
                    while (1)
                    {
                        vTaskDelay(pdMS_TO_TICKS(3000));
                        distance = bs_rt_get_distance();
                        if(distance > 25)break;
                    }
                    for (int i = 255; i >= 0; i-=15) {
                        set_BS_led_right(i);
                        vTaskDelay(pdMS_TO_TICKS(25));
                    }

                    
                }            
            }
            
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }

#endif


#ifdef DISPLAY_INCLUDED
    void display_run_task(void *vpParam){

        while (1)
        {
            if(display_en){

                switch (display_target) {
                    case DISPLAY_EN_OFF:
                        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
                        break;
                    case DISPLAY_MAIN_UI:
                        display_main_UI();
                        break;
                    case DISPLAY_SHOW_LOW_BAT:
                        display_low_battery_warning();
                        break;
                    case DISPLAY_SHOW_DNS_SETTING:
                        display_dns_setting();
                        break;
                    case DISPLAY_SHOW_WALKIE_PAIRING:
                        display_show_walkie_pairing();
                        break;
                    case DISPLAY_SHOW_BLUETOOTH_PAIRING:
                        display_show_bluetooth_pairing();
                    default:
                        break;
                }

            }

            vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
        }  

    }
#endif

void walkie_run_task(void *vpParam){

    while (1)
    {
        if(sendOver == 1){
            // speakOut=0;
            // int samples_read = I2Sread(samples_16bit,128);
            // covert_bit(samples_16bit,samples_8bit,samples_read);
            // walkie_snt(samples_8bit,samples_read);

            printf("WAlkie out\n");
            vTaskDelay(pdMS_TO_TICKS(28));
            
        }else{
            vTaskDelay(pdMS_TO_TICKS(28));
            speakOut=1;
        }
    }
    
} 

