#include <globalVar.h>


uint8_t get_device_type(void){


    return 0;

}
esp_err_t set_device_type(uint8_t device_n){


    return ESP_OK;
}


void init_spiffs(void) {
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "storage",
        .max_files = 5,
        .format_if_mount_failed = true
    };
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));

    size_t total = 0, used = 0;
    esp_err_t res = esp_spiffs_info(conf.partition_label, &total, &used);

    if(res == ESP_OK){
        ESP_LOGI("SPIFF", "Total: %d, Used: %d, Left: %d", total, used, total - used);
    }else{
        ESP_LOGI("SPIFF", "No");
    }
}