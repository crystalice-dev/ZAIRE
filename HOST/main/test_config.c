#include <globalVar.h>
#include <esp_timer.h>
#include "esp_rom_sys.h"


#define TRIG_PIN 47
#define ECHO_PIN 45
#define MAX_DISTANCE_CM       600  // Maximum measurable distance in cm
#define MIN_DETECT_DISTANCE   -1 //ft - When the helmet alert rider of potential object (4 - motorcycle 2 bicycle) -- to be tested
#define MAX_DETECT_DISTANCE   15 //ft - When the helmet does not alert rider of potential object (6 - motorcycle 4 bicycle) -- to be tested
#define TIMEOUT_US            (MAX_DISTANCE_CM * 58)  // Timeout in microseconds

void ultrasonic_init()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << TRIG_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = 0,
        .pull_up_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    io_conf.pin_bit_mask = (1ULL << ECHO_PIN);
    io_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&io_conf);
}

int32_t read_distance_cm()
{
    int64_t start_time, end_time;
    int32_t duration_us;

    // Send a 10µs trigger pulse
    gpio_set_level(TRIG_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(2));
    gpio_set_level(TRIG_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(2));  // ~20µs
    gpio_set_level(TRIG_PIN, 0);

    // Wait for ECHO to go HIGH
    start_time = esp_timer_get_time();
    while (gpio_get_level(ECHO_PIN) == 0) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // timeout waiting for HIGH
        }
    }

    // Measure ECHO HIGH duration
    start_time = esp_timer_get_time();
    while (gpio_get_level(ECHO_PIN) == 1) {
        if ((esp_timer_get_time() - start_time) > TIMEOUT_US) {
            return -1; // timeout waiting for LOW
        }
    }
    end_time = esp_timer_get_time();

    duration_us = end_time - start_time;

    // Convert to centimeters (343 m/s → ~29.1 µs/cm round-trip → /58)
    int32_t distance_cm = duration_us / 58;

    return distance_cm;
}


    void test_run_task(void *vpParam){
         ultrasonic_init();
        while (1)
        {
            int32_t d = read_distance_cm();
            printf("Distance: %ld cm\n", d);
            vTaskDelay(pdMS_TO_TICKS(10));

        }
        

    }