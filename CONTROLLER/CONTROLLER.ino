#include <Arduino.h>
#include "globalVar.h"

bool funcOn = false;
bool conncetionTest = false;
bool isTalkieOn = false;

void connectedLight(){
  if(!funcOn){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }else{
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }
}
void unConnectedLight(){
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
}
void pairingLight(){
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(SLEEP_LED, OUTPUT);

  pinMode(BTN_M, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DWN, INPUT_PULLUP);
  pinMode(BTN_LT, INPUT_PULLUP);
  pinMode(BTN_RT, INPUT_PULLUP);

  pinMode(BTN_FUNC, INPUT_PULLUP);
  pinMode(BTN_WALKIE, INPUT_PULLUP);


  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(CHANNEL, WIFI_SECOND_CHAN_NONE);
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);

  //EEPROM.write(CONNECTED_EEPROM, 0); // To be deleted after first flash
  bool isPaired = EEPROM.read(CONNECTED_EEPROM);

  if(isPaired && digitalRead(BTN_UP) == 1){
    pairingLight();
    for (int ii = 0; ii < 6; ++ii ) {
      uint8_t mac = EEPROM.read(ii);
      helmet.peer_addr[ii] = mac ;
    }
    helmet.channel = CHANNEL; // pick a channel
    helmet.encrypt = 0; // no encryption
    helmetFound = 1;
    
  }else{
    while(helmetFound == 0){
      pairingLight();
      ScanForhelmetPairingMode();
    }
   
  }

  

  xTaskCreate(
    TEST_CONNECTION,
    "TEST CONNECTION",
    5000,
    NULL,
    3,
    NULL
  );

  EEPROM.commit();
  EEPROM.end();
}

void loop() {

  
  if (helmet.channel == CHANNEL) { // check if helmet channel is defined

  

    bool isPaired = managehelmet();
    if (isPaired) {
      
      if(!funcOn){
          
          if(digitalRead(BTN_UP) == 0){
            sendData(BTN_UP_CODE);
            Serial.println(BTN_UP);
            delay(250);
          }

          if(digitalRead(BTN_DWN) == 0){
            sendData(BTN_DWN_CODE);
            delay(250);
          }
          
          if(digitalRead(BTN_LT) == 0){
            sendData(BTN_LT_CODE);
            delay(250);
          }
          
          if(digitalRead(BTN_RT) == 0){
            sendData(BTN_RT_CODE);
            delay(250);
          }
          
          if(digitalRead(BTN_M) == 0){
            sendData(BTN_M_CODE);
            delay(250);
          }
          
        }else{
          if(digitalRead(BTN_UP) == 0){
            sendData(BTN_UP_CODE_FUNC);
            delay(250);
          }

          if(digitalRead(BTN_DWN) == 0){
            sendData(BTN_DWN_CODE_FUNC);
            delay(250);
          }
          
          if(digitalRead(BTN_LT) == 0){
            sendData(BTN_LT_CODE_FUNC);
            delay(250);
          }
          
          if(digitalRead(BTN_RT) == 0){
            sendData(BTN_RT_CODE_FUNC);
            delay(250);
          }
          
          if(digitalRead(BTN_M) == 0){
            sendData(BTN_M_CODE_FUNC);
            delay(250);
          }
          
        }

      if(digitalRead(BTN_FUNC) == 0){
        funcOn = !funcOn;
        delay(250);
        
      }

      if(digitalRead(BTN_WALKIE) == 0){
        sendData(TALKIE_ON);
        isTalkieOn = true;
        delay(250); 
      }else if(digitalRead(BTN_WALKIE) == 1 && isTalkieOn == true){
        isTalkieOn = false;
        sendData(TALKIE_OFF);
        delay(250);
        sendData(TALKIE_OFF);
        delay(250);

      }

    }
  }


}
