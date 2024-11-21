#include <Arduino.h>
#include "globalVar.h"




void serial_Handler(void *vpParam){
  while(1){
    
    if(serialCentral.available() || serialGPS.available() ){
      serialCentralData = serialCentral.readStringUntil('\n');
      gps.encode(serialGPS.read());

      gpsSpeed = gps.speed.mph();
      Serial.println(gpsSpeed);
      serialCentral.println(gpsSpeed);
      
    }else{
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    
  }
}


