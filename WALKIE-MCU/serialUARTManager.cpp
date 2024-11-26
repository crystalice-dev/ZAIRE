#include <Arduino.h>
#include "globalVar.h"


void serial_Handler(void *vpParam){
  while(1){
    
    if(serialCentral.available() || serialGPS.available() ){
      serialCentralData = serialCentral.readStringUntil('\n');

      gps.encode(serialGPS.read());
      gpsSpeed = gps.speed.mph();
      gpsSpeed > GPS_MIN_SPEED ? isAboveSpeed = 1 : isAboveSpeed = 0;
      
    }else{
      vTaskDelay(5 / portTICK_PERIOD_MS);
    }

    serialCentral.println(String(Date + "-" + Time));
    
  }
}


