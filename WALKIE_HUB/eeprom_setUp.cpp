#include <Arduino.h>
#include "globalVar.h"


int start_EEPROM(void){

  esp_err_t err = EEPROM.begin(EEPROM_SIZE);

  if(!err){
    return ESP_FAIL;
  }

  return ESP_OK;
}