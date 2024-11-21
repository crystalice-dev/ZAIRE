#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h> 
#include <EEPROM.h>
#include <FreeRTOS.h>
#include <freertos/task.h>
#include <esp_sleep.h>
#include "communicationCode.h"


// Global copy of helmet
extern esp_now_peer_info_t helmet;
extern bool helmetFound;
extern bool isTalkieOn;
#define CHANNEL 1
#define EEPROM_SIZE      16 // 0-5 will be reserved
#define CONNECTED_EEPROM 10 //bool value

//LEDS
extern bool funcOn;
#define BLUE_LED    16
#define GREEN_LED   17
#define RED_LED     18

#define SLEEP_LED   4 // active when asleep

void connectedLight();
void unConnectedLight();
void pairingLight();

//Buttons
#define BTN_UP   9
#define BTN_DWN  11
#define BTN_LT   10
#define BTN_RT   12 

#define BTN_WALKIE 8
#define BTN_FUNC   13
#define BTN_M      14 // wake up pin


//ESP_Now
void InitESPNow();
bool managehelmet();
void sendData(uint8_t data);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void ScanForhelmetPairingMode();
void TEST_CONNECTION(void *vpParam);



#endif // GLOBAL_VAR_H