#include "globalVar.h"



void init_gpio(void){
    pinMode(ESP_RST, OUTPUT);
    pinMode(ESP_BOOT0, OUTPUT);
    pinMode(CAMERA_EN, OUTPUT);
    pinMode(ON_BOARD_LED, OUTPUT);

    digitalWrite(ESP_RST, LOW);
    digitalWrite(ESP_BOOT0, LOW);
    digitalWrite(CAMERA_EN, LOW);
    digitalWrite(ON_BOARD_LED, LOW);
}