#include <globalVar.h>

esp_err_t wifi_init(void) {
    wifi_config_t default_cfg = { 0 };  // Zero out the struct

    // Copy SSID string safely
    strncpy((char *)default_cfg.ap.ssid, system_settings.WIFI_SSID, sizeof(default_cfg.ap.ssid) - 1);
    default_cfg.ap.ssid_len = strlen(system_settings.WIFI_SSID);
    default_cfg.ap.max_connection = 4;
    default_cfg.ap.authmode = WIFI_AUTH_OPEN;

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
    assert(ap_netif);
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &default_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ESP_OK;
}
