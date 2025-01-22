#include <Arduino.h>
#include "globalVar.h"

int walkie_pin = 0;
int pi_rec_sig = 0;
int emerg_pin  = 0;

int gpio_pin_set_up(){
  pinMode(EMERG_PIN, INPUT_PULLDOWN);
  pinMode(PI_REC_SIG, INPUT_PULLDOWN);
  pinMode(WALKIE_PIN, INPUT_PULLDOWN);
  pinMode(PURPOSE_LED, OUTPUT);

  //BUZZER_PIN
  if(digitalRead(EMERG_PIN) == ESP_OK && digitalRead(PI_REC_SIG) == ESP_OK){
    return ESP_OK;
  }
  
  return ESP_FAIL;

}
