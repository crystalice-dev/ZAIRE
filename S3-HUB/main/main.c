/*
    TITLE: S3-HUB
    DESC: handles ESP_NOW walkie functions; camera; <helmet>BlindSpot Detection; 

*/


#include <globalVar.h>


void app_main(void){
    esp_err_t ret;
    // Initialize NVS -- ALWAYS FIRST
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    if(zaire_system_check() == ESP_FAIL){
        ESP_LOGE("INIT", "Failed to Init Zaire Helmets System");
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_restart();
    }


    #if DEVICE_TYPE != DEVICE_TYPE_TEST
        xTaskCreate(gpio_run_task, "GPIO TASK", 4096, NULL, 4, &gpio_task_handler);
        xTaskCreate(host_run_task, "UART TASK", 10000, NULL, 6, &host_task_handler);
        // xTaskCreate(h3_run_task, "H3 TASK", 10000, NULL, 6, &h3_task_handler);
        xTaskCreate(bk_run_task, "BK TASK", 4096, NULL, 6, &h3_task_handler);
        xTaskCreate(walkie_run_task, "BK TASK", 4096, NULL, 7, &walkie_task_handler);

        #ifdef CAMERA_INCLUDED
            xTaskCreate(camera_btn_run_task, "camera_btn_run_task",4096, NULL, 2, &camera_btn_task_handler);
        #endif
    #else
        xTaskCreate(test_run_task, "TEST TASK", 4096, NULL, 7, NULL);
    #endif

    
    bk_init();
    vTaskDelay(pdMS_TO_TICKS(1000));

    // walkie_discover_peers();

    // while (1)
    // {
    //     uart_write_bytes(HOST_UART_NUM, "B:CRYSTAL ICE", strlen("B:CRYSTAL ICE"));
    //     vTaskDelay(pdMS_TO_TICKS(50));
    //     uart_flush(HOST_UART_NUM);
    //     vTaskDelay(pdMS_TO_TICKS(2000));
    // }
}
