#include <Arduino.h>
#include "globalVar.h"




void uart_run_task(void *vpParam){

  while(1){

    if(serialCentral.available()){
      String str = serialCentral.readStringUntil('\n');  // Correctly use String to hold the input
      int data = atoi(str.c_str());                     // Convert String to const char* and then to int
      central_uart_rec(data);                           // Send data to handler

    }

    vTaskDelay(pdMS_TO_TICKS(10));

  }

}