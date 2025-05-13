#include "globalVar.h"


nvs_handle_t walkie_addr_nvs_registered;
nvs_handle_t remote_addr_nvs_registered;
nvs_handle_t server_nvs_handler;

esp_err_t NVS_init(void){
    esp_err_t err;

    err = NVS_start(WALKIE_NVS_NAMESPACE, &walkie_addr_nvs_registered);

    if(err != ESP_OK){
        return ESP_FAIL;
    }

    err = NVS_start(REMOTE_NVS_NAMESPACE, &remote_addr_nvs_registered);
    if(err != ESP_OK){
        return ESP_FAIL;
    }

    err = NVS_start(SERVER_NVS_NAMESPACE, &server_nvs_handler);
    if (err != ESP_OK) {
        return err; // Or ESP_FAIL if you want to generalize
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


esp_err_t NVS_readblob(nvs_handle_t handle, const char *key, void *out_struct, size_t expected_size) {
    size_t blob_size = 0;
    esp_err_t err = nvs_get_blob(handle, key, NULL, &blob_size);

    if (err == ESP_OK) {
        if (blob_size != expected_size) {
            return ESP_ERR_INVALID_SIZE;
        }

        err = nvs_get_blob(handle, key, out_struct, &blob_size);
        return err; // return ESP_OK or whatever err nvs_get_blob gives
    }

    return err; // ESP_ERR_NVS_NOT_FOUND or other error
}

esp_err_t NVS_writeblob(nvs_handle_t handle, const char *key, const void *in_struct, size_t size) {
    esp_err_t err = nvs_set_blob(handle, key, in_struct, size);
    if (err != ESP_OK) return err;

    return nvs_commit(handle); // Don't forget to commit!
}


esp_err_t NVS_erase(nvs_handle_t handler, const char *key){

    return ESP_OK;
}
esp_err_t NVS_close(nvs_handle_t handler){

    return ESP_OK;
}

esp_err_t NVS_write_settings(){

    // system_settings.WALKIE_STATUS = ;
    // system_settings.AUTO_DASHCAM = 0;
    // system_settings.BLINDSPOT_MONITORING = 1;
    // system_settings.AUTO_BACK_LIGHT = 1;
    // system_settings.TURN_SIGNAL_DURATION = 5;

    // strncpy(system_settings.DEVICE_NAME, "Helmet_Alpha_TEST123", sizeof(system_settings.DEVICE_NAME));
    

    if(NVS_writeblob(server_nvs_handler, SERVER_NVS_NAMESPACE, &system_settings, sizeof(system_settings)) != ESP_OK){
        ESP_LOGE("NVS", "NOTHING WRITTEN");
    }

    return ESP_OK;
}