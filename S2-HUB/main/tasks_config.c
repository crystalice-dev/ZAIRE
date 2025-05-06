#include <globalVar.h>


TaskHandle_t gpio_task_handler = NULL;
TaskHandle_t uart_task_handler = NULL;
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
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
}

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