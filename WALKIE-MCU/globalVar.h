#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H


#include <Arduino.h>
#include <esp_now.h>
#include <Wire.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <HardwareSerial.h>
#include <NewPing.h>
#include <BH1750.h>
#include <RTClib.h>
#include <Adafruit_AHTX0.h>
#include <TinyGPS++.h>
#include <driver/i2s.h>
#include "pin_config.h"
#include "serialCommunicationIndex.h"
#include "Audioi2s.h"
#include "transport.h"



//Walkie
void WalkieTalkie(void *vpParam);

//Serial Communication
extern String serialCentralData;
extern HardwareSerial serialCentral;
extern HardwareSerial serialGPS;
void serial_Handler(void *vpParam);
void serialCentral_handler(int data);

//GPS
extern int gpsSpeed;
extern TinyGPSPlus gps;

//Accessory Manager
void ACCESSORY_MANAGER_TASK(void *vpParam);

//Light Sensor BH1750
#define dayTimeLED            255
#define nightTimeLED          75
extern bool is_LIGHT_SENSOR_ACTIVE;
extern BH1750 lightSensor;
void lightManager(void);
void dayMode(void);
void nightMode(void);

//RTC
extern String Date;
extern String Time;
extern RTC_DS3231 rtc;
void RTCManager(void);

//AHT Temperature Sensor
#define MIN_RUNNING_TEMP  82
extern bool is_AHT_TEMP_SENSOR_ACTIVE;
extern Adafruit_AHTX0 aht;
void tempManager(void);

//BlindSpot Monitoring
#define DETECTED_CAR          35 //real is 350 --test 35
#define MIN_DISTANCE          10 //real is 100 --test 10
#define GPS_MIN_SPEED         -1
#define MAX_DISTANCE          450
extern const int BS_RIGHT_LED_PWM;       // PWM channel (0-15)
extern const int BS_LEFT_LED_PWM;       // PWM channel (0-15)
extern const int pwmFrequency;  // PWM frequency in Hz
extern const int pwmResolution;    // PWM resolution in bits (1-16)
extern bool isAboveSpeed;
extern int pwmBSLightOn;
extern int pwmBSLightOFF;
extern NewPing sonar_RIGHT_BACK;
extern NewPing sonar_RIGHT_SIDE;
extern NewPing sonar_LEFT_BACK;
extern NewPing sonar_LEFT_SIDE;
void BS_LEFT_MANAGEMENT_SYSTEM(void *vpParam);
void BS_RIGHT_MANAGEMENT_SYSTEM(void *vpParam);

//buzzer
void buzzerCaptureSoundSuccess();
void buzzerCaptureSoundFailed();

#endif // GLOBAL_VAR_H