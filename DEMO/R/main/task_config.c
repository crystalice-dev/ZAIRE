#include "globalVar.h"

TaskHandle_t gpio_top_btn_task_handler = NULL;
TaskHandle_t gpio_left_btn_task_handler = NULL;
TaskHandle_t gpio_right_btn_task_handler = NULL;
TaskHandle_t gpio_left_led_task_handler = NULL;
TaskHandle_t gpio_right_led_task_handler = NULL;
TaskHandle_t gpio_top_led_task_handler = NULL;

led_blink_state_t top_led_state = LED_OFF;
led_blink_state_t left_led_state = LED_OFF;
led_blink_state_t right_led_state = LED_OFF;

//Turn Signals
bool left_turn_on = 0;
bool right_turn_on = 0;

void gpio_top_btn_run_task(void *vpParam){
    if(gpio_get_level(TOP_BTN) == HIGH){
        top_led_state = LED_BLINK_FAST;
        pairing_mode = 1;
    }

    pairing_mode = 0;
    while (1){
        if(gpio_get_level(TOP_BTN) == HIGH){
            vTaskDelay(pdMS_TO_TICKS(250));
            if(gpio_get_level(TOP_BTN) == LOW){
                vTaskDelay(pdMS_TO_TICKS(500));
                if(gpio_get_level(TOP_BTN) == HIGH){
                    //OPTION -- CODE 0x__
                    vTaskDelay(pdMS_TO_TICKS(250));
                    top_led_state = LED_BLINK_FAST;
                    while (1)
                    {
                        if(gpio_get_level(TOP_BTN) == LOW)break;
                        vTaskDelay(pdMS_TO_TICKS(10));

                    }
                    vTaskDelay(pdMS_TO_TICKS(250));
                    
                }else{
                    //PLAY-PAUSE MEDIA
                    if(right_turn_on){
                        top_led_state = LED_OFF;
                        right_turn_on = 0;
                    }else{
                        top_led_state = LED_BLINK;
                        right_turn_on = 1;
                    }
                }
            }else{
                //FRONT-WHITE LED_on
                vTaskDelay(pdMS_TO_TICKS(250));
                while (1)
                {
                    if(gpio_get_level(TOP_BTN) == LOW)break;
                    vTaskDelay(pdMS_TO_TICKS(10));

                }
                vTaskDelay(pdMS_TO_TICKS(250));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    

}

void gpio_left_btn_run_task(void *vpParam){

    while (pairing_mode)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    

    while (1){
        if(gpio_get_level(LEFT_BTN) == HIGH){
            vTaskDelay(pdMS_TO_TICKS(250));
            if(gpio_get_level(LEFT_BTN) == LOW){
                vTaskDelay(pdMS_TO_TICKS(500));
                if(gpio_get_level(LEFT_BTN) == HIGH){
                    //DOWN VOLUME
                    vTaskDelay(pdMS_TO_TICKS(250));
                    top_led_state = LED_BLINK_FAST;
                    while (1)
                    {
                        if(gpio_get_level(LEFT_BTN) == LOW)break;
                        vTaskDelay(pdMS_TO_TICKS(10));

                    }
                    vTaskDelay(pdMS_TO_TICKS(250));
                    
                }else{
                    //TURN LEFT SIGNAL
                    if(left_led_state){
                        left_led_state = LED_OFF;
                        left_turn_on = 0;
                    }else{
                        left_led_state = LED_BLINK;
                        left_turn_on = 1;
                    }
                }
            }else{
                //NEXT TRACK
                vTaskDelay(pdMS_TO_TICKS(250));
                while (1)
                {
                    if(gpio_get_level(LEFT_BTN) == LOW)break;
                    vTaskDelay(pdMS_TO_TICKS(10));

                }
                vTaskDelay(pdMS_TO_TICKS(250));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    

}

void gpio_right_btn_run_task(void *vpParam){

    while (pairing_mode)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    while (1){
        if(gpio_get_level(RIGHT_BTN) == HIGH){
            vTaskDelay(pdMS_TO_TICKS(250));
            if(gpio_get_level(RIGHT_BTN) == LOW){
                vTaskDelay(pdMS_TO_TICKS(500));
                if(gpio_get_level(RIGHT_BTN) == HIGH){
                    //DOWN VOLUME
                    vTaskDelay(pdMS_TO_TICKS(250));
                    right_led_state = LED_BLINK_FAST;
                    while (1)
                    {
                        if(gpio_get_level(RIGHT_BTN) == LOW)break;
                        vTaskDelay(pdMS_TO_TICKS(10));

                    }
                    vTaskDelay(pdMS_TO_TICKS(250));
                    
                }else{
                    //TURN LEFT SIGNAL
                    if(right_turn_on){
                        right_led_state = LED_OFF;
                        right_turn_on = 0;
                    }else{
                        right_led_state = LED_BLINK;
                        right_turn_on = 1;
                    }
                }
            }else{
                //NEXT TRACK
                vTaskDelay(pdMS_TO_TICKS(250));
                while (1)
                {
                    if(gpio_get_level(RIGHT_BTN) == LOW)break;
                    vTaskDelay(pdMS_TO_TICKS(10));

                }
                vTaskDelay(pdMS_TO_TICKS(250));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    

}

void gpio_left_led_run_task(void *vpParam){

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    

}

void gpio_right_led_run_task(void *vpParam){

    while (1)
    {
        switch (left_led_state){
            case LED_OFF:
                gpio_set_level(LEFT_LED, LOW);
                break;

            case LED_BLINK:
                gpio_set_level(LEFT_LED, HIGH);
                vTaskDelay(pdMS_TO_TICKS(500));
                gpio_set_level(LEFT_LED, LOW);
                vTaskDelay(pdMS_TO_TICKS(500));
                break;

            case LED_BLINK_FAST:
                gpio_set_level(LEFT_LED, HIGH);
                vTaskDelay(pdMS_TO_TICKS(100));
                gpio_set_level(LEFT_LED, LOW);
                vTaskDelay(pdMS_TO_TICKS(100));
                break;
            default:
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
    

}

void gpio_top_led_run_task(void *vpParam){

    while (1)
    {
        switch (top_led_state){
            case LED_OFF:
                gpio_set_level(RIGHT_LED, LOW);
                break;

            case LED_BLINK:
                gpio_set_level(RIGHT_LED, HIGH);
                vTaskDelay(pdMS_TO_TICKS(500));
                gpio_set_level(RIGHT_LED, LOW);
                vTaskDelay(pdMS_TO_TICKS(500));
                break;

            case LED_BLINK_FAST:
                gpio_set_level(RIGHT_LED, HIGH);
                vTaskDelay(pdMS_TO_TICKS(100));
                gpio_set_level(RIGHT_LED, LOW);
                vTaskDelay(pdMS_TO_TICKS(100));
                break;
            default:
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
    

}

