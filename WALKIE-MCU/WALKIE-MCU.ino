/*
*
*    Author  -> YANN KABAMBI
*    Title   -> ZAIRE_HELMET_WALKIE_MCU_FIRMWARE
*    Version -> 2.0
*    Describ: WALKIE - BLIND SPOT MONITORE - GPS - LIGHT - RTC
*    walkie author -> zuoyi001
*                  -> https://github.com/zuoyi001/ESP32_walkie_talkie
*
*/

#include <Arduino.h>
#include "globalVar.h"
  
HardwareSerial serialCentral(1);
HardwareSerial serialGPS(2);
String serialCentralData;

//GPS
int gpsSpeed = -1;
TinyGPSPlus gps;   


//BLIND SPOT MONITORING
NewPing sonar_RIGHT_BACK(BS_RIGHT_BACK_TRIG, BS_RIGHT_BACK_ECHO, MAX_DISTANCE);
NewPing sonar_RIGHT_SIDE(BS_RIGHT_SIDE_TRIG, BS_RIGHT_SIDE_ECHO, MAX_DISTANCE);
NewPing sonar_LEFT_BACK(BS_LEFT_BACK_TRIG, BS_LEFT_BACK_ECHO, MAX_DISTANCE);
NewPing sonar_LEFT_SIDE(BS_LEFT_SIDE_TRIG, BS_LEFT_SIDE_ECHO, MAX_DISTANCE);
const int BS_RIGHT_LED_PWM = 0;       // PWM channel (0-15)
const int BS_LEFT_LED_PWM = 1;       // PWM channel (0-15)
const int pwmFrequency = 5000;  // PWM frequency in Hz
const int pwmResolution = 8;    // PWM resolution in bits (1-16)
int pwmBSLightOn = 255;
int pwmBSLightOFF = 0;
bool isAboveSpeed = 0;
//Sensors
bool is_LIGHT_SENSOR_ACTIVE = false;
bool is_AHT_TEMP_SENSOR_ACTIVE = false;
//Light Sensor
BH1750 lightSensor;
bool lighterSenser_Active;
float lux = 0;
//Temp
Adafruit_AHTX0 aht;

//RTC
String Date;
String Time;
RTC_DS3231 rtc;

void setup(){
  Wire.begin();
  serialCentral.begin(115200, SERIAL_8N1, SERIAL_CENTRAL_RX, SERIAL_CENTRAL_TX);
  serialGPS.begin(9600, SERIAL_8N1, SERIAL_GPS_RX, SERIAL_GPS_TX);
  Serial.begin(1200);

  pinMode(WALKIE_PIN, INPUT_PULLUP);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED, OUTPUT); //TO BE REMOVED

  //Init Walkie
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  I2SInit();

  //LED setup
  ledcSetup(BS_RIGHT_LED_PWM, pwmFrequency, pwmResolution);
  ledcSetup(BS_LEFT_LED_PWM, pwmFrequency, pwmResolution);
  ledcAttachPin(BS_RIGHT_LED, BS_RIGHT_LED_PWM);
  ledcAttachPin(BS_LEFT_LED, BS_LEFT_LED_PWM);


  //setup Temp
  if(aht.begin()){
    is_AHT_TEMP_SENSOR_ACTIVE = true;
  }
  //setup BlindSpot
  if(lightSensor.begin()){
    is_LIGHT_SENSOR_ACTIVE = true;
  }
  if(!rtc.begin()){
    Serial.println("RTC not INIT");
  }
 
  //FreeRTOS
  xTaskCreate(
    WalkieTalkie,
    "WalkieTalkie",
    10000,
    NULL,
    9,
    NULL
  );

  xTaskCreate(
    ACCESSORY_MANAGER_TASK,
    "ACCESSORY_MANAGER_TASK",
    2500,
    NULL,
    4,
    NULL
  );

   xTaskCreate(
    serial_Handler,
    "serial_Handler",
    2000,
    NULL,
    4,
    NULL
  );


  xTaskCreate(
    BS_LEFT_MANAGEMENT_SYSTEM,
    "BS_LEFT_MANAGEMENT_SYSTEM",
    2000,
    NULL,
    9,
    NULL
  );

  xTaskCreate(
    BS_RIGHT_MANAGEMENT_SYSTEM,
    "BS_RIGHT_MANAGEMENT_SYSTEM",
    2000,
    NULL,
    9,
    NULL
  );

}

void loop(){
 RTCManager();
 delay(2000);
}