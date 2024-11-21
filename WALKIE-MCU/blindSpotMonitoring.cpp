#include <Arduino.h>
#include "globalVar.h"




void BS_LEFT_MANAGEMENT_SYSTEM(void *vpParam){
  
  while(1){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}


void BS_RIGHT_MANAGEMENT_SYSTEM(void *vpParam){

 while(1){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}