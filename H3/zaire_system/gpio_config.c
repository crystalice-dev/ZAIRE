#include "globalVar.h"



void init_gpio(void){
    pinMode(HOST_BOOT0, OUTPUT);
    pinMode(WALKIE_BOOT0, OUTPUT);
    pinMode(CAMERA_EN, OUTPUT);

    digitalWrite(HOST_BOOT0, LOW);
    digitalWrite(WALKIE_BOOT0, LOW);
    digitalWrite(CAMERA_EN, LOW);
}