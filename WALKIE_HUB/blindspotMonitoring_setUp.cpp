#include <Arduino.h>
#include "globalVar.h"


const int BS_RIGHT_LED_PWM = 0;       // PWM channel (0-15)
const int BS_LEFT_LED_PWM = 1;       // PWM channel (0-15)
const int pwmFrequency = 5000;  // PWM frequency in Hz
const int pwmResolution = 8;    // PWM resolution in bits (1-16)
uint8_t lightMode = 1; // 1 - Day; 0 - Night

int pwmBSLightOn = 255;
int pwmBSLightOFF = 0;

int blindspot_lights_init(void){
  
  pinMode(LED_R_SIG, INPUT_PULLDOWN);
  pinMode(LED_L_SIG, INPUT_PULLDOWN);
  esp_err_t err0 = ledcSetup(BS_RIGHT_LED_PWM, pwmFrequency, pwmResolution);
  esp_err_t err1 = ledcSetup(BS_LEFT_LED_PWM, pwmFrequency, pwmResolution);
  ledcAttachPin(BS_RIGHT_LED, BS_RIGHT_LED_PWM);
  ledcAttachPin(BS_LEFT_LED, BS_LEFT_LED_PWM);

  if(!err0 || !err1){
    return ESP_FAIL;
  }

  return ESP_OK;

}