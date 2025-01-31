/*
        TITLE: ZAIRE HELMETS CAMERA MODULE
        AUTHOR: YANN KABAMBI
        FIRMWARE VER: 1.0
        DESC: HANDLE DASHCAM - NO AUDIO AS OF VERSION 1.0
              HANDLE CAMERA SCENERY PHOTO CAPTURE
              HANDLE JDY-67 COMMUNICATION
        NOTE: As for version 1.0, data for "VISION" is stored in the the /home/zairehemets/zaire_vision/vision.zhf
*/

#include "./globalVar.h"




int main(void){

    //init wiringPisudo 
    if(wiringPiSetup() < 0){
        printf("Failed init wiringPi\n");
        return -1;
    }

    //setup UART -- Central && JDY
     if((serialPort = serialOpen("/dev/ttyAMA0", 9600)) < 0){
            printf("Could not open Serial port\n");
            return 1;
    }

    //setup pthreads
    pthread_t centralPthread;


    pthread_create(&centralPthread, NULL, central_task, NULL);


    pthread_join(centralPthread, NULL);

    return 0;

}