#include <Arduino.h>
#include "globalVar.h"



int gpio_pin_set_up(){
  pinMode(EMERG_PIN, INPUT_PULLDOWN);
  pinMode(PI_REC_SIG, INPUT_PULLDOWN);
  pinMode(WALKIE_PIN, INPUT_PULLDOWN);
  pinMode(PURPOSE_LED, OUTPUT);

  //BUZZER_PIN
  if(digitalRead(EMERG_PIN) == ESP_OK && digitalRead(PI_REC_SIG) == ESP_OK && digitalRead(WALKIE_PIN) == ESP_OK && digitalRead(WALKIE_PIN) == ESP_OK){
    return ESP_OK;
  }
  
  return ESP_FAIL;

}