#include <globalVar.h>

uint8_t device_sta_mac[6];
uint8_t helmet_ap_mac[6];

esp_err_t init_wifi(void){

    wifi_config_t default_cfg = {
        .sta = {
            .ssid = "",
            .password = "",
            .channel = ESP_NOW_CHANNEL
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
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &default_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_read_mac(device_sta_mac, ESP_MAC_WIFI_STA);

    return ESP_OK;
}

esp_err_t espNow_init(void){

    esp_err_t err = esp_now_init();

    if(err != ESP_OK){
        return ESP_FAIL;
    }

    ESP_ERROR_CHECK(esp_now_register_send_cb(esp_now_sent_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(esp_now_recv_cb));

    return ESP_OK; // Placeholder for actual ESP-NOW initialization code
}

esp_err_t gpio_init(void){

    esp_err_t err;

    gpio_config_t top_config = { // Init at 0
            .pin_bit_mask = (1ULL << TOP_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
        err = gpio_config(&top_config);
        if(err){
            return ESP_FAIL;
        }

    gpio_config_t left_config = { // Init at 1
            .pin_bit_mask = (1ULL << LEFT_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
    err = gpio_config(&left_config);
    if(err){
        return ESP_FAIL;
    }
    gpio_config_t right_config = { // Init at 2
            .pin_bit_mask = (1ULL << RIGHT_BTN), // Select GPIO pin
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,  // Enable pull-down resistor
            .intr_type = GPIO_INTR_DISABLE
        };
    err = gpio_config(&right_config);
    if(err){
        return ESP_FAIL;
    }
    
    return ESP_OK; // Placeholder for actual GPIO initialization code

}