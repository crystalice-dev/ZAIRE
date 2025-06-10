#include <globalVar.h>


TaskHandle_t gpio_task_handler = NULL;
TaskHandle_t gps_uart_task_handler = NULL;
TaskHandle_t h3_uart_task_handler = NULL;
TaskHandle_t walkie_uart_task_handler = NULL;
TaskHandle_t i2c_task_handler = NULL;
TaskHandle_t display_task_handler = NULL;
TaskHandle_t led_strip_task_handler = NULL;
TaskHandle_t bs_left_monitor_handler = NULL;
TaskHandle_t bs_right_monitor_handler = NULL;

void gpio_run_task(void *vpParam){

    #ifdef REMOTE_INCLUDED
        //Check if remote pairing is requested
        if(gpio_get_level(PURPOSE_BTN) == HIGH){
            led_target_stage = REMOTE_PAIRING;
            remote_pairing_requested();
        }
    #endif

    while (1)
    {

        if(gpio_get_level(PURPOSE_BTN) == HIGH){
            vTaskDelay(pdMS_TO_TICKS(250));
            if(gpio_get_level(PURPOSE_BTN) == HIGH){
                vTaskDelay(pdMS_TO_TICKS(2000));
                if(gpio_get_level(PURPOSE_BTN) == HIGH){


                    if(remote_pairing_requested_btn == 0){
                        dns_server_active = !dns_server_active;

                        if(dns_server_active == 1){
                            double_quick_buzz();
                            start_dns_server();
                        }else{
                            
                            if(stop_dns_server() == ESP_OK){
                                quick_buzz();
                            }else{
                                esp_restart();
                            }
                        }
                        
                        vTaskDelay(pdMS_TO_TICKS(1000));
                    }
                }
            }else{
                printf("PURPOSE PRESSED\n");
            }
        }

        #ifdef DISPLAY_INCLUDED
            if(gpio_get_level(DISPLAY_EN_BTN)){
                vTaskDelay(pdMS_TO_TICKS(250));
                display_quick_show();
            }
        #endif
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    

}

void h3_uart_run_task(void *vpParam){
    char h3_data[BUF_SIZE];

    while (1)
    {
        // Read and process Walkie UART data
        int h3_len = uart_read_bytes(H3_UART_NUM, h3_data, BUF_SIZE, pdMS_TO_TICKS(100));
        if (h3_len > 0) {
            printf("%s\n", (const char *)h3_data);
            memset(h3_data, 0, sizeof(h3_data));  // Clears the buffer
        }
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }

}

void walkie_uart_run_task(void *vpParam){
    char walkie_data[BUF_SIZE];

    while (1)
    {
        // Read and process Walkie UART data
        int walkie_len = uart_read_bytes(WALKIE_UART_NUM, walkie_data, BUF_SIZE, pdMS_TO_TICKS(100));
        if (walkie_len > 0) {
            walkie_uart_received((const char *)walkie_data);
            memset(walkie_data, 0, sizeof(walkie_data));  // Clears the buffer
        }
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }

}

void gps_uart_run_task(void *vpParam){
    
    while (1){
        
        char gps_data[BUF_SIZE];

        int gps_len = uart_read_bytes(GPS_UART_NUM, gps_data, BUF_SIZE - 1, pdMS_TO_TICKS(100));
        if (gps_len > 0) {
            gps_data[gps_len] = '\0';  // Null-terminate

            char *line = strtok(gps_data, "\n\r");
            while (line != NULL) {
                if (strstr(line, GPS_LAT_LON_SPEED_CODE) == line) {
                    gps_get_lat_lon_speed(line);
                } else if (strstr(line, GPS_ALT_CODE) == line) {
                    gps_get_alt(line);
                }
                line = strtok(NULL, "\n\r");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
}

void i2c_run_task(void *vpParam){

    battery_quick_start(); //Quick battery monitor setup

    while (1)
    {
        // BATTERY_VOLTAGE = battery_get_voltage();
        // BATTERY_STATUS = battery_get_soc();
        
        lux = bh1750_read_lux();
        //printf("lux: %.2f\n", bh1750_read_lux()); 

        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY_FIVE_SEC));
    }
    
}

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
                    case DISPLAY_SHOW_DNS_IP:
                        display_dns_IP();
                        break;
                    default:
                        break;
                }

            }

            vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
        }  

    }
#endif

#ifdef LIGHTS_INCLUDED
    void led_strip_run_task(void *vpParam){

        led_strip_handle_t led_strip = configure_led_stip();
        led_welcome_animation(led_strip);
        while (1)
        {
            switch (led_target_mode[0]){
                case LED_OFF:
                    led_front_white_off();
                    break;
                
                case FRONT_WHITE_ON:
                    led_front_white_on();
                    break;

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
                default:
                    break;
            }

            vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
        }
        

    }
#endif

#ifdef BLINDSPOT_INCLUDED


    void bs_left_monitor_task(void *vpParam){

        while (1){
            int32_t distance = bs_lt_get_distance();
            
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }

    void bs_right_monitor_task(void *vpParam){

        while (1){
            int32_t distance = bs_rt_get_distance();
            
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }

#endif