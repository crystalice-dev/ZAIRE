#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "./peerGlobalCodeAddr.h"

//Global Var
#define HIGH                    1
#define LOW                     0



//GPIO BOARD ASSIGN
#define GPIO_NUM_0              27
#define GPIO_NUM_1              28
#define GPIO_NUM_2              3 //I2C_SDA
#define GPIO_NUM_3              5 //I2C_SCK
#define GPIO_NUM_4              7
#define GPIO_NUM_5              29 //BUZZER
#define GPIO_NUM_6              31 //
#define GPIO_NUM_8              24 //CS
#define GPIO_NUM_9              21 //D0 -- MISO
#define GPIO_NUM_10             19 //CMD -- MOSI
#define GPIO_NUM_11             23 //SCK
#define GPIO_NUM_12             32 //SD_WRITE
#define GPIO_NUM_13             33
#define GPIO_NUM_14             8 //<--- RESERVED --->
#define GPIO_NUM_15             10//<--- RESERVED --->
#define GPIO_NUM_16             36
#define GPIO_NUM_17             11
#define GPIO_NUM_18             12
#define GPIO_NUM_19             35
#define GPIO_NUM_20             38
#define GPIO_NUM_21             40
#define GPIO_NUM_22             15
#define GPIO_NUM_23             16
#define GPIO_NUM_24             18
#define GPIO_NUM_25             22
#define GPIO_NUM_26             37 
void gpio_init();

//BUZZER
#define BUZZER                  GPIO_NUM_5

//I2C
#define I2C_SDA                 GPIO_NUM_2
#define I2C_SCK                 GPIO_NUM_3
void i2c_init();

//SDCard
#define SD_CMD                  GPIO_NUM_10
#define SD_SCK                  GPIO_NUM_11
#define SD_D0                   GPIO_NUM_9
#define SD_CS                   GPIO_NUM_8
void sdCard_init();

//Camera
#define START_DASHCAM_CMD       "ffmpeg -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 -c:v libx264 -preset veryfast -f mp4 ~/zaire_vision/DashCam/"
#define STOP_DASHCAM_CMD        ""
#define CAPTURE_CMD             ""
#define DASHCAM_MODE            1 //Record full video
#define CAPTURE_MODE            0 // capture images -- photo
#define MKDIR_DASHCAM           "mkdir ~/zaire_vision/DashCam/"
#define MKDIR_CAPTURE           "mkdir ~/zaire_vision/Photo/"
#define DASHCAM_FOLDER          "~/zaire_vision/DashCam/"
#define CAPTURE_FOLDER          "~/zaire_vision/Photo/"
void camera_init();

//VISION
#define MKDIR_VISION            "mkdir ~/zaire_vision/VISION/"
#define VISION_FOLDER           "~/zaire_vision/VISION/"

//uart
#define BUFFER_SIZE             1024
extern int serialPort;
extern char data[BUFFER_SIZE];
extern int  data_index;
extern char buffer;
void central_uart_rec(char* str);
void jdy_uart_snd(char* cmd);

//pthread tasks
void* gpio_task(void* arg);
void* central_task(void* arg);
void* camera_task(void* arg);

#endif
