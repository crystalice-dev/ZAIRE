#include <Arduino.h>
#include "globalVar.h"


//Accessory Manager
void ACCESSORY_MANAGER_TASK(void *vpParam){

  while(1){
    if(is_LIGHT_SENSOR_ACTIVE){
      lightManager();
    }
    
    if(is_AHT_TEMP_SENSOR_ACTIVE){
      tempManager();
    }

    vTaskDelay( 1000 / portTICK_PERIOD_MS); //3 seconds
  }

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
 
  if(lux > 700){
    dayMode();
  }else{
    nightMode();
  }

}

//Temperature
void tempManager(void){
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  // Convert temperature to Fahrenheit
  float temperatureF = (temp.temperature * 9.0 / 5.0) + 32.0;

  //turn on fan or send overheat warning --
  //HIGH -> OFF
  //LOW -> ON

  if(temperatureF > MIN_RUNNING_TEMP){
    digitalWrite(FAN_PIN, 0);
  }else{
    digitalWrite(FAN_PIN, 1);
  }

}

void RTCManager(void){
  DateTime now = rtc.now();

  int day = now.day();
  int month = now.month();
  int year = now.year();

  int hour = now.hour();
  int minutes = now.minute();
  int seconds = now.second();

  String dayStr = day < 10 ? "0" + String(day) : String(day);
  String monthStr = month < 10 ? "0" + String(month) : String(month);

  String hourStr = hour < 10 ? "0" + String(hour) : String(hour);
  String minutesStr = minutes < 10 ? "0" + String(minutes) : String(minutes);
  String secondsStr = seconds < 10 ? "0" + String(seconds) : String(seconds); 

  Date = (monthStr + "-" + dayStr + "-" + String(year));

  Time = (hourStr + "-" + minutesStr + "-" + secondsStr);

}

