#include <globalVar.h>


TaskHandle_t gpio_task_handler = NULL;
TaskHandle_t uart_task_handler = NULL;
TaskHandle_t i2c_task_handler = NULL;
TaskHandle_t display_task_handler = NULL;


void gpio_run_task(void *vpParam){

    while (1)
    {
        if(gpio_get_level(DISPLAY_EN_BTN)){
            vTaskDelay(pdMS_TO_TICKS(250));
            display_quick_show();
        }

        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
    

}

void uart_run_task(void *vpParam){
    
    while (1){
        
        char gps_data[BUF_SIZE];
        char walkie_data[BUF_SIZE];
        char h3_data[BUF_SIZE];

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


         // Read and process Walkie UART data
        int walkie_len = uart_read_bytes(WALKIE_UART_NUM, walkie_data, BUF_SIZE, pdMS_TO_TICKS(100));
        if (walkie_len > 0) {
            printf("%s\n", (const char *)walkie_data);
            memset(walkie_data, 0, sizeof(walkie_data));  // Clears the buffer
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