#include <Arduino.h>
#include "globalVar.h"



// Init ESP Now with fallback
void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    delay(1000);
    ESP.restart();
  }
}

void configAPName(){

  if(digitalRead(PURPOSE_BTN) == 0){
    digitalWrite(PURPOSE_LED, HIGH);
    delay(500);
    digitalWrite(PURPOSE_LED, LOW);
    delay(500);
    digitalWrite(PURPOSE_LED, HIGH);
    configDeviceAP_PairingMode();
    delay(3000);
    digitalWrite(PURPOSE_LED, LOW);
    ESP.restart();

  }else{
    digitalWrite(PURPOSE_LED, HIGH);
    delay(1000);
    configDeviceAP();
    digitalWrite(PURPOSE_LED, LOW);

  }

}

// config AP SSID
void configDeviceAP() {
  const char *SSID = "zairehelmet_1";
  bool result = WiFi.softAP(SSID, "helmet_1_Password", CHANNEL, 0);
  
}

void configDeviceAP_PairingMode() {
  const char *SSID = "zairehelmetpairingmode_1";
  bool result = WiFi.softAP(SSID, "helmet_1_Password", CHANNEL, 0);
  
}

// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  if(*data != TEST_CODE ){
    
    switch(*data){

      case TALKIE_ON:
        digitalWrite(WALKIE_PIN, LOW);
      
        break;
      case TALKIE_OFF:
        digitalWrite(WALKIE_PIN, HIGH);
      
        break;
      
      default:
        break;

    }


  }
}