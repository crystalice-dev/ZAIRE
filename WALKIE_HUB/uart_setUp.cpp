#include <Arduino.h>
#include "globalVar.h"


//UART
HardwareSerial serialGPS(0);
HardwareSerial serialCentral(1);

void uart_init(void){
  serialGPS.begin(GPS_BAUD_RATE,SERIAL_8N1, GPS_UART_RX_PIN, GPS_UART_TX_PIN);
  serialCentral.begin(CENTRAL_BAUD_RATE,SERIAL_8N1, CENTRAL_UART_RX_PIN, CENTRAL_UART_RX_PIN);

}