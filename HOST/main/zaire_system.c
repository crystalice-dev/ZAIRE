#include <globalVar.h>


esp_err_t zaire_system_check(){

    if(init_spiffs() != ESP_OK){
        return ESP_FAIL;
    }

    if(NVS_init() != ESP_OK){
        return ESP_FAIL;
    }

    if(wifi_init() != ESP_OK){
        return ESP_FAIL;
    }

    if(gpio_pin_init() != ESP_OK){
        return ESP_FAIL;
    }

    #ifdef DISPLAY_INCLUDED
        if(display_init() != ESP_OK){
            return ESP_FAIL;
        }
    #endif   
    
    if(i2c_init() != ESP_OK){
        return ESP_FAIL;
    }

    if(bh1750_init() != ESP_OK){
        return ESP_FAIL;
    }

    if(uart_init() != ESP_OK){
        return ESP_FAIL;
    }
    
    if(init_i2s() != ESP_OK){
        return ESP_FAIL;
    }

    if(init_usb_mic() != ESP_OK){
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t zaire_load_nvs_data(){

    WALKIE_STATUS = NVS_read(server_nvs_handler, "WALKIE_STATUS");
    AUTO_DASHCAM = NVS_read(server_nvs_handler, "AUTO_DASHCAM");
    BLINDSPOT_MONITORING = NVS_read(server_nvs_handler, "BLINDSPOT_MONITORING");
    AUTO_BACK_LIGHT = NVS_read(server_nvs_handler, "AUTO_BACK_LIGHT");
    TURN_SIGNAL_DURATION = NVS_read(server_nvs_handler, "TURN_SIGNAL_DURATION");
    

    return ESP_OK;
}


esp_err_t init_spiffs(void) {
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "storage",
        .max_files = 5,
        .format_if_mount_failed = true
    };
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));

    size_t total = 0, used = 0;
    esp_err_t res = esp_spiffs_info(conf.partition_label, &total, &used);

    return res;
}