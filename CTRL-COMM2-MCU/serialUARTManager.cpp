#include "freertos/portmacro.h"
#include <Arduino.h>
#include "globalVar.h"




int serialNumberHandler(char C = 0, char D = 0, char U = 0){
  int Cent = (C - '0') * 100;
  int Dix  = (D - '0') * 10;
  int Un   = (U - '0') * 1;

  return Cent + Dix + Un;
}

void serialWalkieTask(void *vpParam){ //SPEED - LATITUDE - LONGITUDE
  while(1){
    if(serialWalkie.available()){

      serialData_Walkie = serialWalkie.readStringUntil('\n');
      Serial.println(serialData_Walkie);


    }else{

      vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    serialWalkie.println("Hello Walkie");
    
  }
}


void serialBT_Task(void *vpParam){ // Date - Time - USER SETTINGS
  while(1){
    
    // if(serialBT.available()){

    //   serialData_BT = serialBT.readStringUntil('\n');

    //   Date = serialData_BT.substring(0,0);
    //   Time = serialData_BT.substring(0,0);

    //   char C = serialData_BT[0];
    //   char D = serialData_BT[0];
    //   char U = serialData_BT[0];
    //   GPS_SPEED = serialNumberHandler(C, D, U);

    // }else{
    //   vTaskDelay(10 / portTICK_PERIOD_MS);
    // }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}