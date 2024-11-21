/*
*
*    Author  -> YANN KABAMBI
*    Title   -> ZAIRE_HELMET_BT_MCU_FIRMWARE
*    Version -> 1.0
*    Describ: A2DP/HFP - BLIND SPOT - BUZZER - BLE - EEPROM 
*
*/


#include <stdio.h>
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_a2dp_api.h"
#include "esp_hf_client_api.h"
#include "esp_gap_bt_api.h"
#include "esp_avrc_api.h"
#include "nvs_flash.h"

// Define AVRCP callback function (as needed)
static void avrc_ct_callback(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param)
{
    switch (event) {
        case ESP_AVRC_CT_CONNECTION_STATE_EVT:
            // Handle connection state events
            break;
        case ESP_AVRC_TG_PASSTHROUGH_CMD_EVT:
            // Handle pass-through command events (e.g., play/pause)
            break;
        default:
            break;
    }
}

// Define the A2DP event handler
static void a2dp_event_handler(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param) {
    switch (event) {
        case ESP_A2D_CONNECTION_STATE_EVT:
        case ESP_A2D_AUDIO_STATE_EVT:
        case ESP_A2D_AUDIO_CFG_EVT:
        case ESP_A2D_PROF_STATE_EVT:
        case ESP_A2D_SNK_PSC_CFG_EVT:
        case ESP_A2D_SNK_SET_DELAY_VALUE_EVT:
        case ESP_A2D_SNK_GET_DELAY_VALUE_EVT: 
    default:
    
        break;
    }
}

// Define the A2DP data callback
static void a2dp_data_callback(const uint8_t *data, uint32_t len) {
    printf("A2DP Data Received: %ld bytes\n", len);  // Use %ld for uint32_t
    // Here, you would process the incoming audio data
}

// Define the HFP event handler
static void hfp_event_handler(esp_hf_client_cb_event_t event, esp_hf_client_cb_param_t *param) {
    switch (event) {
        case ESP_HF_CLIENT_CONNECTION_STATE_EVT:
        case ESP_HF_CLIENT_AUDIO_STATE_EVT:
        case ESP_HF_CLIENT_RING_IND_EVT:
        case ESP_HF_CLIENT_CIND_CALL_EVT:
        default:
            break;
    }
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize Bluetooth Controller
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret != ESP_OK) {
        printf("Bluetooth controller initialization failed: %d\n", ret);
        return;
    }

    // Enable Bluetooth Controller (Classic Bluetooth mode or Dual Mode)
    ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM); // Dual Mode: Classic + BLE
    if (ret != ESP_OK) {
        printf("Bluetooth controller enable failed: %d\n", ret);
        return;
    }

    // Initialize Bluetooth stack (Bluedroid)
    ret = esp_bluedroid_init();
    if (ret != ESP_OK) {
        printf("Bluedroid initialization failed: %d\n", ret);
        return;
    }

    // Enable Bluetooth stack
    ret = esp_bluedroid_enable();
    if (ret != ESP_OK) {
        printf("Bluedroid enable failed: %d\n", ret);
        return;
    }

    printf("Bluetooth controller initialized successfully!\n");
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

    // Initialize AVRCP (Audio/Video Remote Control Profile)
    ret = esp_avrc_ct_init();  // AVRCP controller must be initialized before A2DP
    if (ret != ESP_OK) {
        printf("AVRCP controller initialization failed: %d\n", ret);
        return;
    }

    // Register AVRCP callback (optional but recommended if using AVRCP control features)
    ret = esp_avrc_ct_register_callback(avrc_ct_callback);  // Define this callback function as needed
    if (ret != ESP_OK) {
        printf("AVRCP callback registration failed: %d\n", ret);
        return;
    }

    // Initialize A2DP Sink (Audio Streaming)
    ret = esp_a2d_sink_init();
    if (ret != ESP_OK) {
        printf("A2DP sink initialization failed: %d\n", ret);
        return;
    }

    // Register A2DP event handler
    ret = esp_a2d_register_callback(a2dp_event_handler);
    if (ret != ESP_OK) {
        printf("A2DP callback registration failed: %d\n", ret);
        return;
    }

    // Register A2DP data callback
    ret = esp_a2d_sink_register_data_callback(a2dp_data_callback);
    if (ret != ESP_OK) {
        printf("A2DP data callback registration failed: %d\n", ret);
        return;
    }

    // Initialize HFP Client (Hands-Free Profile)
    ret = esp_hf_client_init();
    if (ret != ESP_OK) {
        printf("HFP client initialization failed: %d\n", ret);
        return;
    }

    // Register HFP event handler
    ret = esp_hf_client_register_callback(hfp_event_handler);
    if (ret != ESP_OK) {
        printf("HFP callback registration failed: %d\n", ret);
        return;
    }

    printf("Bluetooth A2DP, AVRCP, and HFP initialized successfully!\n");

    // You can now handle audio playback and phone call features based on A2DP and HFP functionality.
}
