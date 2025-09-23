#include <globlaVar.h>

void app_main(void)
{
    esp_err_t ret;
    // Initialize NVS -- ALWAYS FIRST
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if(ret != ZAIRE_OK)esp_restart();

    //System init and checks
    if(zaire_system_init() != ZAIRE_OK){vTaskDelay(pdMS_TO_TICKS(2000)); esp_restart();};

    //xTask create
    xTaskCreate(walkie_btn_task_run, "walkie_btn_task_run", 4096, NULL, 4, &walkie_btn_task_handler);
    xTaskCreate(purpose_left_btn_task_run, "purpose_left_btn_task_run", 4096, NULL, 4, &purpose_left_btn_task_handler);
    xTaskCreate(purpose_right_btn_task_run, "purpose_right_btn_task_run", 4096, NULL, 4, &purpose_right_btn_task_handler);
    xTaskCreate(display_task_run, "display_task_run", 4096, NULL, 2, &display_task_handler);
    xTaskCreate(bk3266_task_run, "bk3266_task_run", 4096, NULL, 4, &bk3266_task_handler);
    xTaskCreate(walkie_task_run, "walkie_task_run", 5120, NULL, 8, &walkie_task_handler);

    quick_buzz();
    //====== LAST SYSTEM CALL BEFORE RETURN 0 ========
    vTaskDelay(pdMS_TO_TICKS(2000));
    display_off();

}
