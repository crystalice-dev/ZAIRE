#include <Arduino.h>
#include "globalVar.h"


//UART
HardwareSerial serialGPS(0);
HardwareSerial serialCentral(1);

void uart_init(void){
  //serialGPS.begin(GPS_BAUD_RATE,SERIAL_8N1, GPS_UART_RX_PIN, GPS_UART_TX_PIN);
  serialCentral.begin(CENTRAL_BAUD_RATE,SERIAL_8N1, CENTRAL_UART_RX_PIN, CENTRAL_UART_TX_PIN);

}

void central_uart_snd(const int data){
  serialCentral.println(data);
  vTaskDelay(pdMS_TO_TICKS(500));
}

void central_uart_rec(const int data){
  
  switch(data){

    case GET_WALKIE_ADDR:
      Serial.println("SERVE ADDR");
      central_uart_snd(OPEN_ADDR_INSERT);
      vTaskDelay(pdMS_TO_TICKS(500));
      
      break;

    default:
      break;

  }

}