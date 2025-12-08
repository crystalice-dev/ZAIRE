#include <globalVar.h>



TaskHandle_t walkie_btn_task_handler = NULL;
TaskHandle_t purpose_left_btn_task_handler = NULL;
TaskHandle_t purpose_right_btn_task_handler = NULL;
TaskHandle_t display_task_handler = NULL;
TaskHandle_t bk3266_task_handler = NULL;
TaskHandle_t walkie_task_handler = NULL;

static bool right_special_click = false;

void purpose_right_btn_task_run(void *vpParam){
    
    while (1)
    {
        if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
            
            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                while (1){ // While on hold, decrease BT volume 0-16

                    bk3266_send_cmd(PLAYER_VOL_UP);
                    printf("vol up\n");
                    vTaskDelay(pdMS_TO_TICKS(750));
                    if(gpio_get_level(PURPOSE_RIGHT) != HIGH)break;
                }
            
            }else{
                vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
                    vTaskDelay(pdMS_TO_TICKS(250));
                    while (1){ // While on hold, go back to prev media track 
                        bk3266_send_cmd(PLAYER_MEDIA_NXT);
                        printf("next\n");
                        vTaskDelay(pdMS_TO_TICKS(2500));
                        if(gpio_get_level(PURPOSE_RIGHT) != HIGH) break;
                    }

                }else{ // Turn on Goggle display -> Cycle through display menu
                    if(display_special_on == false){
                        display_en = HIGH;
                        display_timer = 3000;
                        display_button_target +=1;
                        if(display_button_target > 6)display_button_target = 1;
                        display_quick_show_menu();
                    }else{
                        right_special_click = true;
                    }
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void purpose_left_btn_task_run(void *vpParam){
    
    while (1)
    {
        if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){

            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                while (1){ // While on hold, increase bt volume 0-16
                    bk3266_send_cmd(PLAYER_VOL_DWN);
                    vTaskDelay(pdMS_TO_TICKS(750));
                    printf("vol dwn\n");
                    if(gpio_get_level(PURPOSE_LEFT) != HIGH)break;
                }
            
            }else{
                vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
                    vTaskDelay(pdMS_TO_TICKS(250));
                    while (1){ // while on hold, go to next media track
                        printf("prev\n");
                        bk3266_send_cmd(PLAYER_MEDIA_PRV);
                        vTaskDelay(pdMS_TO_TICKS(2500));
                        if(gpio_get_level(PURPOSE_LEFT) != HIGH) break;
                    }

                }else{
                    bk3266_PP_CALL();
                    printf("PP\n");
                    vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                }
            }
        }else if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH) {
            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
            
                vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            }else if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                double_quick_buzz();
                printf("video\n");
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
            }
            
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void walkie_btn_task_run(void *vpParam){

    while (1)
    {
        if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){
            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){
                if(is_walkie_on || is_walkie_mute == false){
                    while (gpio_get_level(WALKIE_BTN) == HIGH){
                        walkie_speak = true;
                        printf("on\n");
                        vTaskDelay(pdMS_TO_TICKS(10));
                    }
                    walkie_speak = false;
                    vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                }
            }else if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
                 if(is_walkie_on == true){walkie_mute(); vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));}
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}

void display_timer_run(void *vpParam){
    while (1)
    {
        if(display_timer < 0 && display_special_on == false){
            if(display_button_target > 1){
                display_special_on = true; //disable display button, incase user hit display button during sequence

                switch (display_button_target)
                {
                case DISPLAY_SETTINGS:
                    switch (is_setting_on)
                        {
                        case false:
                            double_quick_buzz();
                            network_settings_mode();
                            start_dns_server();
                            is_setting_on = true;
                            break;
                        case true:
                            network_standard_mode();
                            stop_dns_server();
                            quick_buzz();
                            is_setting_on = false;
                            break;
                        default:
                            break;
                        }
                        vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                    break;
                case DISPLAY_BLUETOOTH:
                    display_target = DISPLAY_SHOW_BK3266_BLUETOOTH_PWR_SEQUENCE;
                    if(!is_bk3266_on){
    
                        double_quick_buzz();
                    }else{

                        quick_buzz();
                    }
                    vTaskDelay(pdMS_TO_TICKS(3000));
                    break;
                case DISPLAY_WALKIE_HOST:
                    double_quick_buzz();
                    walkie_pairing_master();
                    break;
                case DISPLAY_WALKIE_RCVR:
                    double_quick_buzz();
                    walkie_pairing_slave();
                    break;
                case DISPLAY_SYSTEM_RESTART:
                    
                    int count = 4;
                    while (1)
                    {
                        quick_buzz();
                        count -=1;
                        vTaskDelay(pdMS_TO_TICKS(1000));
                        if(right_special_click == true){
                            right_special_click = false;
                            break;
                        }
                        if(count < 0){
                            if(is_walkie_on)peer_leave_mesh();
                            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                            esp_restart();
                        }
                    }
                    break;
                    
                default:
                    break;
                }
                display_special_on = false; //return display button function

            }
            if(display_en == HIGH){
                display_off();
                display_en = LOW;
            }
            vTaskDelay(pdMS_TO_TICKS(50));
        }else{
            display_timer -=1000;
            vTaskDelay(pdMS_TO_TICKS(1000));

        }
    }
    
}

void display_task_run(void *vpParam){

    while (1)
        {
            if(display_en){

                switch (display_target) {
                    case DISPLAY_EN_OFF:
                        vTaskDelay(pdMS_TO_TICKS(10));
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
                    case DISPLAY_SHOW_WALKIE_MASTER_SETTING:
                        display_walkie_MASTER_setting();
                        break;
                    case DISPLAY_SHOW_WALKIE_SLAVE_SETTING:
                        display_walkie_SLAVE_setting();
                        break;
                    case DISPLAY_SHOW_WALKIE_SYNC_SETTING:
                        display_walkie_SYNC_setting();
                        break;
                    case DISPLAY_SHOW_WALKIE_PAIRED_SETTING:
                        display_show_walkie_paired_setting();
                        break;
                    case DISPLAY_SHOW_WALKIE_CANCELED_SETTING:
                        display_show_cancled();
                        break;
                    case DISPLAY_SHOW_WALKIE_MASTER_SEARCH_SETTING:
                        display_show_walkie_master_search_setting();
                        break;
                    case DISPLAY_SHOW_WALKIE_SLAVE_SEARCH_SETTING:
                        display_show_walkie_slave_search_setting();
                        break;
                    case DISPLAY_SHOW_WALKIE_MUTE_SEQUENCE:
                        display_show_walkie_mute_sequence();
                        break;
                    case DISPLAY_SHOW_WALKIE_DELETE_SEQUENCE:
                        display_show_walkie_delete_sequence();
                        break;
                    case DISPLAY_SHOW_WALKIE_ENTER_PAIRING_SEQUENCE:
                        display_show_walkie_enter_pairing_sequence();
                        break;
                    case DISPLAY_SHOW_BK3266_BLUETOOTH:
                        display_show_bk3266_bluetooth();
                        break;
                    case DISPLAY_SHOW_BK3266_BLUETOOTH_PWR_SEQUENCE:
                        display_show_bk3266_bluetooth_pwr_sequence();
                        break;
                    case DISPLAY_SHOW_SYSTEM_RESTART:
                        display_show_system_restart();
                    default:
                        break;
                }
            }

            vTaskDelay(pdMS_TO_TICKS(10));
        }  
}


void bk3266_task_run(void *vpParam){

    char bk3266_data[RX_BUF_SIZE];
    while (1)
    {
        int bk3266_len = uart_read_bytes(BK3266_UART_NUM, bk3266_data, RX_BUF_SIZE - 1, pdMS_TO_TICKS(100));

        if (bk3266_len > 0) {
            printf("%s\n", bk3266_data);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
}

void walkie_task_run(void *vpParm){

    while (1)
    {
        if(walkie_speak){
            speakOut = false;
            int samples_read = I2Sread(samples_16bit, 128);  // Read data
            covert_bit(samples_16bit, samples_8bit, samples_read);  // Convert to 8-bit
            walkie_sendData(samples_8bit, samples_read);  // Transmit data
            vTaskDelay(pdMS_TO_TICKS(10));  // Small delay to prevent tight loop
        }else{
            speakOut = true;
            if (recOver) {
                recOver = false;
            }else{
                i2s_zero_dma_buffer(SPK_I2S_PORT);  // Optional: Clear DMA buffer to stop audio if needed
            }
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
    

}


void test_task_run(void *vpParam){



    while (1)
    {
        top_speed_gps +=5;
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
    

}