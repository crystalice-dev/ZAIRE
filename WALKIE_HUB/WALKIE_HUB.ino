/*

  | Target: ESP32| </br>
  | Envmnt: ARDUINO 2.3.4| </br>
  | vrsion: 5.0 | </br>
  | Author: Yann Kabambi | </br>

  # zaire helmets - WALKIE HUB UNIT
  #### IMPORTANT: ARDUINO IDE -> BOARD MANAGER -> ESP32 by Espressif System VERSION *2.0.17*
  ###### ANY VERSION ABOVE THAT WILL NOT WORK!!!
  (See the README.md file in the upper level 'zaire_helmets' directory for more information about This whole project.)

  The following contains a list of all the responsibilities this firmware has:

  * WALKIE TALKIE with everyone in the MESH
  * GPS.
    * Speed.
    * Location : Longitude - Latitude.
  * RTC -- PCF8563T/5,518.
  * LIGHT SENSOR -- BH1750FVI-TR.
  * Blindspot Lighting
  * SdCard Read/Write data ('CONFIG.zh' || 'CONFIG.zhf' depending on version).

  ### ENJOY - YANN NGOIE KABAMBI !!
  01-19-2025 07:45🕞 


*/
#include <Arduino.h>
#include "globalVar.h"


bool settings_port = 0;

int zaire_system_init(void){

  uart_init();
  xTaskCreate(uart_run_task, "uart_run_task", 2048, NULL, 3, &uartTask_handle);

  delay(1000); // Delay for info to coming incase we are paring

  if(start_EEPROM()){
    return ESP_FAIL;
  }
  
  if(gpio_pin_set_up()){
    return ESP_FAIL;
  }

  if(walkie_setUp()){
    return ESP_FAIL;
  }

  if(blindspot_lights_init()){
    return ESP_FAIL;
  }

  // if(accessories_init()){
  //   return ESP_FAIL;
  // }

  // if(ES8311_init()){ // to be tested with the board
  //   return ESP_FAIL;
  // }

  return ESP_OK;
}

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_0_DATA_PIN, I2C_0_SCL_PIN);
  zaire_system_init();

  xTaskCreate(gpio_run_task, "gpio_run_task", 2048, NULL, 3, &gpioTask_handle);
}

void loop() {
  //chill
}
