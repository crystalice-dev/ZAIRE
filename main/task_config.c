#include <globlaVar.h>



TaskHandle_t walkie_btn_task_handler = NULL;
TaskHandle_t purpose_left_btn_task_handler = NULL;
TaskHandle_t purpose_right_btn_task_handler = NULL;
TaskHandle_t display_task_handler = NULL;
TaskHandle_t bk3266_task_handler = NULL;
TaskHandle_t walkie_task_handler = NULL;

void purpose_left_btn_task_run(void *vpParam){
    
    while (1)
    {
        if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
            
            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_LEFT)){
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                while (1){ // While on hold, decrease BT volume 0-16

                    bk3266_send_cmd(PLAYER_VOL_DWN);
                    vTaskDelay(pdMS_TO_TICKS(500));
                    if(gpio_get_level(PURPOSE_LEFT) != HIGH)break;
                }
            
            }else{
                vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                if(gpio_get_level(PURPOSE_LEFT)){
                    vTaskDelay(pdMS_TO_TICKS(500));
                    while (1){ // While on hold, go back to prev media track 
                        bk3266_send_cmd(PLAYER_MEDIA_PRV);
                        vTaskDelay(pdMS_TO_TICKS(750));
                        if(gpio_get_level(PURPOSE_LEFT) != HIGH) break;
                    }

                }else{ //PAUSE MEDIA - END CALL - ANSWER CALL -- VIA GPIO38(ESP32S3) -> P.P/CALL(GPIO4)[BK3266]
                    bk3266_PP_CALL();

                    peer_leave_mesh();
                    vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                }
            }
        }else if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){ 
            // Take a picture
            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(WALKIE_BTN) == HIGH){
            vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
            double_quick_buzz();
            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void purpose_right_btn_task_run(void *vpParam){
    
    while (1)
    {
        if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){

            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_RIGHT)){
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                while (1){ // While on hold, increase bt volume 0-16
                    bk3266_send_cmd(PLAYER_VOL_UP);
                    vTaskDelay(pdMS_TO_TICKS(500));
                    if(gpio_get_level(PURPOSE_RIGHT) != HIGH)break;
                }
            
            }else{
                vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
                    vTaskDelay(pdMS_TO_TICKS(500));
                    while (1){ // while on hold, go to next media track
                        bk3266_send_cmd(PLAYER_MEDIA_NXT);
                        vTaskDelay(pdMS_TO_TICKS(750));
                        if(gpio_get_level(PURPOSE_RIGHT) != HIGH) break;
                    }

                }else{ // Turn on Goggle display -> Cycle through display menu
                    display_target = DISPLAY_MAIN_UI;
                    printf("HHHLLK => %d\n", peers_in_mesh);
                    vTaskDelay(pdMS_TO_TICKS(3000));
                    display_off();

                }
            }
        }else if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW) {
            //Settings mode
            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
            if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == HIGH){
                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));

                switch (is_setting_on)
                {
                case false:
                    double_quick_buzz();
                    network_settings_mode();
                    start_dns_server();
                    display_dns_setting();
                    is_setting_on = true;
                    break;
                case true:
                    quick_buzz();
                    is_setting_on = false;
                    break;
                default:
                    break;
                }
                vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
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
            if(gpio_get_level(WALKIE_BTN) == HIGH){

                if(is_walkie_on == false || is_walkie_mute == true){
                    vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                    if(is_walkie_on){
                        display_target = DISPLAY_SHOW_WALKIE_DELETE_SEQUENCE;
                        vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));

                        if(gpio_get_level(WALKIE_BTN) == HIGH){
                            display_target = DISPLAY_SHOW_WALKIE_ENTER_PAIRING_SEQUENCE;
                            vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                            
                            if(gpio_get_level(WALKIE_BTN) == HIGH){
                                display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
                                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                                display_off();
                            }else{
                                walkie_pairing_sequence();
                            }
                            
                        }else{
                            peer_leave_mesh();
                        }

                    }else{
                        if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){
                            //Enter host pairing mode
                            display_en = true;
                            display_target = DISPLAY_SHOW_WALKIE_MASTER_SETTING;
                            double_quick_buzz();
                            vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                            if(gpio_get_level(WALKIE_BTN) == HIGH){
                                //Enter slave pairing mode
                                display_target = DISPLAY_SHOW_WALKIE_SLAVE_SETTING;
                                double_quick_buzz();
                                vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
                                if(gpio_get_level(WALKIE_BTN) == HIGH){
                                    //Cancle pairing request
                                    display_target = DISPLAY_SHOW_WALKIE_CANCELED_SETTING;
                                    quick_buzz();
                                }else{
                                    walkie_pairing_slave();
                                }
                            }else{
                                walkie_pairing_master();
                            }
                            vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                        }
                    }

                }else{
                    while (gpio_get_level(WALKIE_BTN) == HIGH){
                        walkie_speak = true;
                        vTaskDelay(pdMS_TO_TICKS(10));
                    }
                    walkie_speak = false;
                    vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
                    
                }

            }else{
                if(is_walkie_on == true){walkie_mute(); vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));}
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
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
            printf("Send walkie data\n");
        }else{
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
    

}