#include <globalVar.h>


bool sendOver=1;
bool recOver=0;
bool speakOut;
int32_t *samples_32bit;
int16_t *samples_16bit;
uint8_t *samples_8bit ;
int16_t *recive_16bit;
int16_t *output_16bit;

bool mesh_system_active = CLOSED;
uint8_t walkie_address[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t peer_addresses[10][6];
uint8_t number_paired_peers = 1; // 1 is us


esp_err_t init_wifi(void){
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    ESP_ERROR_CHECK(esp_wifi_set_channel((wifi_second_chan_t)3, WIFI_SECOND_CHAN_NONE));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(false));
    esp_err_t err = esp_wifi_start();

    if(err != ESP_OK){
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t init_esp_now(void){
    
    esp_err_t err = esp_now_init();

    if(err != ESP_OK){
        return ESP_FAIL;
    }

    ESP_ERROR_CHECK(esp_now_register_send_cb(esp_now_sent_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(esp_now_recv_cb));

    return ESP_OK;

}
void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status){

}

void esp_now_recv_cb(const uint8_t *mac_addr,  const uint8_t *data, int data_len){

}

esp_err_t add_peer_to_mesh(uint8_t *mac_addr){

    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, mac_addr, ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.encrypt = false;

    if (esp_now_add_peer(&peer_info) == ESP_OK) {
        if(number_paired_peers < mesh_system_max_connection){
            memcpy(peer_addresses[number_paired_peers], mac_addr, 6);
            number_paired_peers++;
            return ESP_OK;
        } else {
            esp_now_del_peer(mac_addr);
            return ESP_FAIL;
        }
    } else {
        return ESP_FAIL;
    }
    
    vTaskDelay(pdMS_TO_TICKS(5)); // Gives time for connection
    number_paired_peers += 1;
    return ESP_OK;
}

esp_err_t remove_peer_from_mesh(uint8_t *mac_addr){

    return esp_now_del_peer(mac_addr);
}