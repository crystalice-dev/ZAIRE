#include <globalVar.h>


settings_t system_settings;

esp_err_t zaire_system_check(){
    init_spiffs();
    NVS_init();
    zaire_load_nvs_data();
    wifi_init();
    gpio_pin_init();

    #ifdef BLINDSPOT_INCLUDED
        bs_monitor_init();
    #endif

    #ifdef DISPLAY_INCLUDED
        if(display_init() != ESP_OK){
            return ESP_FAIL;
        }
    #endif   
    
    i2c_init();
    bh1750_init();
    uart_init();
    init_i2s();
    init_usb_mic();

    return ESP_OK;
}

esp_err_t zaire_load_nvs_data(){

    memset(&system_settings, 0, sizeof(system_settings)); // Always a good idea before filling

    if(NVS_readblob(server_nvs_handler, SERVER_NVS_NAMESPACE, &system_settings, sizeof(system_settings)) != ESP_OK ){
        ESP_LOGE("NVS", "ZAIRE SETTINGS NOT LOADED");
        return ESP_FAIL;
    }

    printf("%s\n", system_settings.WIFI_SSID);

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