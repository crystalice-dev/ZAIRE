#include "globalVar.h"


nvs_handle_t walkie_addr_nvs_registered;
nvs_handle_t server_nvs_handler;

bool nvs_start(const char *namespace, const nvs_handle_t *handler) {
    
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, handler);
    if (err == ESP_OK) {
        return ESP_OK;
    }
   
     return ESP_FAIL;
}


bool nvs_write(nvs_handle_t handler, const char *key, uint8_t value) {
    esp_err_t err = nvs_set_i32(handler, key, value);
    if (err == ESP_OK) {
        nvs_commit(handler);
        return ESP_OK;
    }
    
    return ESP_FAIL;
}

uint8_t nvs_read(nvs_handle_t handler, const char *key) {
    int32_t temp_value; // Temporary variable for nvs_get_i32
    esp_err_t err = nvs_get_i32(handler, key, &temp_value);

    // If successful, cast to uint8_t and return
    if (err == ESP_OK) {
        if (temp_value >= 0 && temp_value <= UINT8_MAX) { // Ensure the value fits in uint8_t
            return (uint8_t)temp_value;
        }
    }

    // Return a default value (e.g., 0) on error or out-of-range value
    return 0;
}