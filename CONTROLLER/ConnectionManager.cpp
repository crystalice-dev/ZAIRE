#include <Arduino.h>
#include "globalVar.h"

esp_now_peer_info_t helmet;
bool helmetFound = 0;

void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    delay(1000);
    ESP.restart();
  }

}

// Scan for helmets in AP mode
void ScanForhelmetPairingMode(){
  int16_t scanResults = WiFi.scanNetworks(false, false, false, 300, CHANNEL); // Scan only on one channel
  // reset on each scan
  
  memset(&helmet, 0, sizeof(helmet));
  if (scanResults == 0) {
    
  } else {
    for (int i = 0; i < scanResults; ++i) {
      // Print SSID and RSSI for each device found
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);
      delay(10);
      // Check if the current device starts with `helmet`
      if (SSID.indexOf("zairehelmetpairingmode") == 0) {
      
        // Get BSSID => Mac Address of the helmet
        int mac[6];
        if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
          for (int ii = 0; ii < 6; ++ii ) {
            helmet.peer_addr[ii] = (uint8_t) mac[ii];
            EEPROM.write(ii, (uint8_t) mac[ii]);
          }
        }

        helmet.channel = CHANNEL; // pick a channel
        helmet.encrypt = 0; // no encryption
        helmetFound = 1;
        // we are planning to have only one helmet in this example;
        // Hence, break after we find one, to be a bit efficient
        break;
      }
    }
  }


  // clean up ram
  WiFi.scanDelete();
}

bool managehelmet() {
  if (helmet.channel == CHANNEL) {


    // check if the peer exists
    bool exists = esp_now_is_peer_exist(helmet.peer_addr);
    if ( exists) {
      return true;
    } else {
      // helmet not paired, attempt pair
      esp_err_t addStatus = esp_now_add_peer(&helmet);
      if (addStatus == ESP_OK) {
        // Pair success
     
        return true;
      } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        // How did we get so far!!
        
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
      
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
       
        return true;
      } else {
        
        return false;
      }
    }
  } else {

    return false;
  }
}


void TEST_CONNECTION(void *vpParam){

  while(1){
    if(digitalRead(BTN_WALKIE)){
      sendData(TEST_CODE);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }else{
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }

}


// send data
void sendData(uint8_t data) {
  const uint8_t *peer_addr = helmet.peer_addr;
  esp_err_t result = esp_now_send(peer_addr, &data, sizeof(data));
  data != TEST_CODE? Serial.println(data) : NULL;

}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  status == ESP_NOW_SEND_SUCCESS ? connectedLight() : unConnectedLight();

}
