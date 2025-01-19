#include <Arduino.h>
#include "globalVar.h"


RTC_DS3231 rtc;
BH1750 lightSensor;



int accessories_init(void){

  esp_err_t err0 = lightSensor.begin();


  if(!err0){
    return ESP_FAIL;
  }

  return ESP_OK;

}

//Light Sensor
void dayMode(void){
  pwmBSLightOn = dayTimeLED;
}

void nightMode(void){
  pwmBSLightOn = nightTimeLED;
}

void lightManager(void){
  float lux = lightSensor.readLightLevel();
 
  if(lux < 1000){
    if(lightMode){
      nightMode();
    }
  }else{
    if(!lightMode){
      dayMode();
    }
  }

}