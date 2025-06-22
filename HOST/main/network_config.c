#include <globalVar.h>

esp_err_t wifi_init(void) {

    wifi_config_t default_cfg = {
        .sta = {
            .ssid = "",
            .password = "",
            .channel = 1
        }
    };
    
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
    assert(ap_netif);
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    return ESP_OK;

}

void wifi_send_ap_bssid(){

    char http_server_start[512];
    uint8_t mac[6];

    //Get MAC address (BSSID) of our AP
    esp_wifi_get_mac(WIFI_IF_AP, mac);

    vTaskDelay(pdMS_TO_TICKS(100));
    snprintf(dns_server_bssid, sizeof(dns_server_bssid),
             "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    
    snprintf(http_server_start, sizeof(http_server_start), "H|%s|%s\n", dns_server_ssid, dns_server_bssid);
    h3_uart_send_data(http_server_start);

}


esp_err_t wifi_settings_mode() {

    wifi_config_t default_cfg = { 
        .ap = {
            .ssid = "ZAIRE_SETTING",
            .password = "",
            .channel = 3,
            .ssid_len = strlen("ZAIRE_SETTING"),
            .authmode = WIFI_AUTH_OPEN,
            .max_connection = 10,
        },
    };

    // Copy SSID string from system settings
    // strncpy((char *)default_cfg.ap.ssid, system_settings.WIFI_SSID, sizeof(default_cfg.ap.ssid) - 1);
    // default_cfg.ap.ssid_len = strlen(system_settings.WIFI_SSID);

    // Set Wi-Fi to Access Point mode
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &default_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    vTaskDelay(pdMS_TO_TICKS(200));
    wifi_send_ap_bssid();

    return ESP_OK;
}



esp_err_t wifi_standard_mode(){
    wifi_config_t default_cfg = {
        .sta = {
            .ssid = "",
            .password = "",
            .channel = 1
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &default_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ESP_OK;
}

esp_err_t wifi_remote_pairing_mode() {
    
    wifi_config_t slave_cfg = {
        .ap = {
            .ssid = DEVICE_REMOTE_PAIRING_NAME,
            .password = "",
            .channel = ESP_REMOTE_NOW_CHANNEL,
            .ssid_len = strlen(DEVICE_REMOTE_PAIRING_NAME),
            .authmode = WIFI_AUTH_OPEN,
            .max_connection = 1,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &slave_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(esp_now_sent_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(esp_now_recv_cb));

    return ESP_OK;
}
