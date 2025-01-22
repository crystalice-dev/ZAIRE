#include <Arduino.h>
#include "globalVar.h"


uint8_t walkie_mac_addr[6];
uint8_t peerBroadcastAddress[120][6];
uint8_t pairedPeer = 0;
uint8_t failedPairing = 0;

void InitESPNow(void){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel((wifi_second_chan_t)3, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  esp_wifi_get_mac(WIFI_IF_STA, walkie_mac_addr);
  if (esp_now_init() == ESP_FAIL) {
    //Beep and falsh 2x then restart
    // alert central we are restarting
    central_uart_snd(RESTARTING_DEVICE);
    esp_restart();
  }

}

int getPeerAddr(void){

  esp_now_peer_info_t peerInfo = {};

  if(pairedPeer < 1){
    Serial.println("No helmets");
    return 0;
  }

  for(int i = 0; i < pairedPeer; i++){
        memcpy(&peerInfo.peer_addr, peerBroadcastAddress[i], 6);
        if (!esp_now_is_peer_exist(peerBroadcastAddress[i])){
          
            esp_err_t result;
            result = esp_now_add_peer(&peerInfo);
            if (result != ESP_OK){
              failedPairing +=1;
            } 
        }
    }

  return 0;

}

void espNow_on_data_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len){

}

void espNow_on_data_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status){

}

int walkie_setUp(void){
  InitESPNow();
  getPeerAddr();
  esp_now_register_recv_cb(espNow_on_data_recv_cb);
  esp_now_register_send_cb(espNow_on_data_send_cb);
  return ESP_OK;

}