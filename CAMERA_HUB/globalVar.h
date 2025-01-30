#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H



//Global Var
#define HIGH                    1
#define LOW                     0

#define Delay_Time              5


//GLOABL GPIOs -- Follow Board Number

#define GPIO_NUM_25             22  //CAMERA ON-OFF
#define GPIO_NUM_5              29 //BUZZER
#define GPIO_NUM_6              31 //
#define GPIO_NUM_8              24 //CS
#define GPIO_NUM_9              21 //D0 -- MISO
#define GPIO_NUM_10             19 //CMD -- MOSI
#define GPIO_NUM_11             23 //SCK
#define GPIO_NUM_12             32 //SD_WRITE
#define GPIO_NUM_13             33


//BUZZER
#define BUZZER                  GPIO_NUM_5

//SDCard
#define SD_CMD                  GPIO_NUM_10
#define SD_SCK                  GPIO_NUM_11
#define SD_D0                   GPIO_NUM_9
#define SD_CS                   GPIO_NUM_8

#define SD_READ                 GPIO_NUM_12
#define SD_WRITE                GPIO_NUM_13

//Camera
#define CAMERA_ON               GPIO_NUM_25
#define START_DASHCAM_CMD       "ffmpeg -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 -c:v libx264 -preset veryfast -f mp4 ~/zaire_vision/DashCam/"
#define STOP_DASHCAM_CMD        ""
#define CAPTURE_CMD             ""
#define DASHCAM_MODE            1 //Record full video
#define CAPTURE_MODE            0 // capture images -- photo
#define MKDIR_DASHCAM           "mkdir ~/zaire_vision/DashCam/"
#define MKDIR_CAPTURE           "mkdir ~/zaire_vision/Photo/"
#define DASHCAM_FOLDER          "~/zaire_vision/DashCam/"
#define CAPTURE_FOLDER          "~/zaire_vision/Photo/"

//VISION
#define MKDIR_VISION            "mkdir ~/zaire_vision/VISION/"
#define VISION_FOLDER           "~/zaire_vision/VISION/"

#endif
