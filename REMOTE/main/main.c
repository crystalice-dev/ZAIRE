#include <globalVar.h>

void app_main(void)
{
    esp_err_t ret;
    // Initialize NVS -- ALWAYS FIRST
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    //Inits
    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(espNow_init());
    ESP_ERROR_CHECK(gpio_init());

    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_OUTPUT); // Set GPIO15 as output

    while (1)
    {
        gpio_set_level(GPIO_NUM_15, 1); // Set GPIO15 high
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 1 second
        gpio_set_level(GPIO_NUM_15, 0); // Set GPIO15 low
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 1 second
    }
    
    
}