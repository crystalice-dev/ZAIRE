#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include "communicationCode.h"
#include <HardwareSerial.h>
#include <EEPROM.h>
#include "pin_config.h"
#include "serialCommunicationIndex.h"


//Serial Communication
extern String serialData_BT;
extern String serialData_Walkie;
extern HardwareSerial serialWalkie;
extern HardwareSerial serialBT;
void serialWalkieTask(void *vpParam);
void serialBT_Task(void *vpParam);


//Controller Config
#define CHANNEL 1
void InitESPNow();
void configAPName();
void configDeviceAP();
void configDeviceAP_PairingMode();
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);


//Camera && SD Card Config
extern String Date;
extern String Time;
extern String speed;
extern String filePath;
extern int GPS_SPEED;
extern bool readyToCreateFolder;
extern bool CAMERA_AUTO_STATUS;
extern bool isCameraActive;
extern String Date;
extern String Time;
extern bool isDashCamOn;
extern bool isCaptureOn;
extern unsigned long frame;
bool InitSDCard();
bool InitCamera();
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void createDir(fs::FS &fs, const char * path);
void removeDir(fs::FS &fs, const char * path);
void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void deleteFile(fs::FS &fs, const char * path);
void testFileIO(fs::FS &fs, const char * path);
void Camera_SDCardManager(void *vpParam);
void CapturePhoto();
void DashCam();
void buzzerCaptureSoundSuccess();
void buzzerCaptureSoundFailed();

#endif