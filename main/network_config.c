#include <globlaVar.h>

esp_err_t network_init(void) {
    
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
    assert(ap_netif);
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));


    
    return ZAIRE_OK;

}

esp_err_t network_settings_mode(){

    wifi_config_t default_cfg = { 
        .ap = {
            .ssid = NETWORK_SETTINGS_SSID,
            .password = "",
            .channel = 3,
            .ssid_len = strlen(NETWORK_SETTINGS_SSID),
            .authmode = WIFI_AUTH_OPEN,
            .max_connection = NETWORK_MAX_CONN,
        },
    };

    // Copy SSID string from system settings
    // strncpy((char *)default_cfg.ap.ssid, system_settings.WIFI_SSID, sizeof(default_cfg.ap.ssid) - 1);
    // default_cfg.ap.ssid_len = strlen(system_settings.WIFI_SSID);

    // Set Wi-Fi to Access Point mode
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &default_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    vTaskDelay(pdMS_TO_TICKS(200));

    return ZAIRE_OK;
}

esp_err_t network_standard_mode(){
    wifi_config_t default_cfg = {
        .sta = {
            .ssid = {0},
            .password = {0},
            .channel = ESP_NOW_CHANNEL
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &default_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ZAIRE_OK;
}

esp_err_t network_pairing_mode_master(){
    
    wifi_config_t master_cfg = {
        .sta = {
            .ssid = {0},
            .password = {0},
            .channel = ESP_NOW_CHANNEL
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &master_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    if(is_esp_now_active == false){
        esp_now_mesh_init(); 
        is_esp_now_active = true;
        esp_read_mac(device_sta_mac, ESP_MAC_WIFI_STA);
        memcpy(peer_addresses[0], device_sta_mac, ESP_NOW_ETH_ALEN);
    }

    return ZAIRE_OK;
}

esp_err_t network_pairing_mode_slave(){

    wifi_config_t slave_cfg = {
        .ap = {
            .ssid = DEVICE_PAIRING_NAME,
            .password = "",
            .channel = ESP_NOW_CHANNEL,
            .ssid_len = strlen(DEVICE_PAIRING_NAME),
            .authmode = WIFI_AUTH_OPEN,
            .max_connection = DEFAULT_SCAN_LIST_SIZE,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &slave_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    if(is_esp_now_active == false){
        esp_now_mesh_init(); 
        is_esp_now_active = true;
        esp_read_mac(device_sta_mac, ESP_MAC_WIFI_STA);
        memcpy(peer_addresses[0], device_sta_mac, ESP_NOW_ETH_ALEN);

    }

    

    return ZAIRE_OK;
}