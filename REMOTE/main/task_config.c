#include <globalVar.h>


TaskHandle_t gpio_top_btn_task_handler = NULL;
TaskHandle_t gpio_left_btn_task_handler = NULL;
TaskHandle_t gpio_right_btn_task_handler = NULL;
TaskHandle_t gpio_left_led_task_handler = NULL;
TaskHandle_t gpio_right_led_task_handler = NULL;
TaskHandle_t gpio_top_led_task_handler = NULL;

led_blink_state_t top_led_state = LED_OFF;
led_blink_state_t left_led_state = LED_OFF;
led_blink_state_t right_led_state = LED_OFF;

void gpio_top_btn_run_task(void *vpParam) {

    if(gpio_get_level(TOP_BTN) == 1) { // set paring mode on
        top_led_state = LED_BLINK; // Set top LED to blink state
        isPairingInvoked = true; // Set pairing invoked flag
        remote_pairing(); // Start pairing process
    } 

    while (1) {
        // Placeholder for actual button handling code
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay to prevent busy-waiting
    }
}

void gpio_left_btn_run_task(void *vpParam) {
    while (1) {
        // Placeholder for actual button handling code
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay to prevent busy-waiting
    }
}

void gpio_right_btn_run_task(void *vpParam) {
    while (1) {
        // Placeholder for actual button handling code
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay to prevent busy-waiting
    }
}

void gpio_left_led_run_task(void *vpParam) {
    while (1) {
        // Placeholder for actual LED handling code
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay to prevent busy-waiting
    }
}

void gpio_right_led_run_task(void *vpParam) {
    while (1) {
        // Placeholder for actual LED handling code
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay to prevent busy-waiting
    }
}

void gpio_top_led_run_task(void *vpParam) {
    while (1) {
        
        switch (top_led_state)
        {
        case LED_OFF:
            gpio_set_level(TOP_LED, 0); // Turn off the top LED
            break;
        
        case LED_STANDBY:
            gpio_set_level(TOP_LED, 1); // Set the top LED to standby state
            break;
        case LED_BLINK:
            gpio_set_level(TOP_LED, 1); // Turn on the top LED
            vTaskDelay(pdMS_TO_TICKS(500)); // Delay for half a second
            gpio_set_level(TOP_LED, 0); // Turn off the top LED
            vTaskDelay(pdMS_TO_TICKS(500)); // Delay for half a second
            break;
        case LED_BLINK_FAST:
            gpio_set_level(TOP_LED, 1); // Turn on the top LED
            vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100 milliseconds
            gpio_set_level(TOP_LED, 0); // Turn off the top LED
            vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100 milliseconds
            break;
        default:
            break;
        }

        vTaskDelay(pdMS_TO_TICKS(10)); // Delay to prevent busy-waiting
    }
}