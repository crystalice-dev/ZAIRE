#include <Arduino.h>
#include "globalVar.h"


TaskHandle_t uartTask_handle = NULL;
TaskHandle_t gpioTask_handle = NULL;


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

void gpio_run_task(void *vpParam){

  while(1){

    int walkie_pin = digitalRead(WALKIE_PIN);
    int pi_rec_sig = digitalRead(PI_REC_SIG);
    int emerg_pin  = digitalRead(EMERG_PIN);

    

    vTaskDelay(pdMS_TO_TICKS(50));
  }

}