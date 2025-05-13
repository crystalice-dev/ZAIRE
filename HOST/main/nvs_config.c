#include "globalVar.h"


nvs_handle_t walkie_addr_nvs_registered;
nvs_handle_t remote_addr_nvs_registered;
nvs_handle_t server_nvs_handler;

char DEVICE_NAME[124] = "ZAIRE VISION";
char WIFI_SSID[124] = "ZAIRE_SETTINGS";
uint8_t WALKIE_STATUS, AUTO_DASHCAM, BLINDSPOT_MONITORING, AUTO_BACK_LIGHT = 0;
uint8_t TURN_SIGNAL_DURATION = 5;

esp_err_t NVS_init(void){

    if(NVS_start(WALKIE_NVS_NAMESPACE, &walkie_addr_nvs_registered)){
        return ESP_FAIL;
    }

    if(NVS_start(REMOTE_NVS_NAMESPACE, &remote_addr_nvs_registered)){
        return ESP_FAIL;
    }

    if(NVS_start(SERVER_NVS_NAMESPACE, &server_nvs_handler)){
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t NVS_start(const char *namespace, const nvs_handle_t *handler) {
    
    esp_err_t err = nvs_open(namespace, NVS_READWRITE, handler);
    if (err == ESP_OK) {
        return ESP_OK;
    }
   
     return ESP_FAIL;
}


esp_err_t NVS_write(nvs_handle_t handler, const char *key, uint8_t value) {
    esp_err_t err = nvs_set_i32(handler, key, value);
    if (err == ESP_OK) {
        nvs_commit(handler);
        return ESP_OK;
    }
    
    return ESP_FAIL;
}

uint8_t NVS_read(nvs_handle_t handler, const char *key) {
    int32_t temp_value; // Temporary variable for nvs_get_i32
    esp_err_t err = nvs_get_i32(handler, key, &temp_value);

    // If successful, cast to uint8_t and return
    if (err == ESP_OK) {
        if (temp_value >= 0 && temp_value <= UINT8_MAX) { // Ensure the value fits in uint8_t
            return (uint8_t)temp_value;
        }
    }

    return 0xFF; // Special code meaning "not found or error"
}

esp_err_t NVS_erase(nvs_handle_t handler, const char *key){

    return ESP_OK;
}
esp_err_t NVS_close(nvs_handle_t handler){

    return ESP_OK;
}