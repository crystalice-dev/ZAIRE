/*
*
*    Author  -> YANN KABAMBI
*    Title   -> ZAIRE_HELMET_CTRL-COMM2_MCU_FIRMWARE
*    Version -> 2.0
*    Describ: CONTROLLER RECEIVER - CAMERA - SD CARD - COMM2 - EMERGENCY_CALLOUT - EEPROM
*    
*                  
*
*/
#include <Arduino.h>
#include "globalVar.h"


//Serial Communication
String serialData_BT = "";
String serialData_Walkie = "";
HardwareSerial serialWalkie(1);
//HardwareSerial serialBT(1);

//Camera & SDCard
String Date = "";
String Time = "";
String speed = "N/A";
String filePath = "";
bool CAMERA_AUTO_STATUS = false;
bool isDashCamOn = false;
bool isCaptureOn = false;
bool isCameraActive = false;
bool readyToCreateFolder = true; // local -- will change to false on start
unsigned long frame = 0;
int GPS_SPEED;

void setup() {

  // put your setup code here, to run once:
  serialWalkie.begin(115200, SERIAL_8N1, SERIAL_WALKIE_RX, SERIAL_WALKIE_TX);
  //serialBT.begin(9600, SERIAL_8N1, SERIAL_BT_RX, SERIAL_BT_TX);
  Serial.begin(9600);

  //pin setup
  pinMode(PURPOSE_BTN , INPUT_PULLUP);
  pinMode(WALKIE_PIN  , OUTPUT); 
  pinMode(PURPOSE_LED , OUTPUT);
  pinMode(POWER_SIGNAL, OUTPUT); 

  digitalWrite(WALKIE_PIN, HIGH); // WALKIE OFF
  digitalWrite(POWER_SIGNAL, HIGH); // HELMET ON -- NOT ASLEEP

  //Buzzer setup
  ledcSetup(BUZZER_CHANNEL, 5000, 8);
  ledcAttachPin(BUZZER, BUZZER_CHANNEL);


  //Controller Config
  WiFi.mode(WIFI_AP);
  configAPName();
  InitESPNow();
  esp_now_register_recv_cb(OnDataRecv);


   //Camera Config
  if(!InitCamera()){
    buzzerCaptureSoundFailed();
  }else{
    isCameraActive = true;
  }


  //SD Card Config
  if(InitSDCard()){
    // Serial.println("SDcard not Init");
    readyToCreateFolder = true;
  }else{
    buzzerCaptureSoundFailed();
    readyToCreateFolder = false;
  }



  //Tasks
  xTaskCreate( // Serial Walkie
    serialWalkieTask,
    "serialWalkieTask",
    2500,
    NULL,
    6,
    NULL
  );

  xTaskCreate(
    serialBT_Task,
    "serialBT_Task",
    2500,
    NULL,
    5,
    NULL
  );
 
}

void loop() {
 //chill

}
