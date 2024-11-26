#include <Arduino.h>
#include "globalVar.h"




//BLIND SPOT MONITORING
void BS_LEFT_MANAGEMENT_SYSTEM(void *vpParam){

  while(1){
    int sonar_L_B = sonar_LEFT_BACK.ping_cm();
    int sonar_L_S = sonar_LEFT_SIDE.ping_cm();

    

    if(sonar_L_B < DETECTED_CAR && sonar_L_B > MIN_DISTANCE && isAboveSpeed == 1){
      while(1){
        ledcWrite(BS_LEFT_LED_PWM, pwmBSLightOn);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
       

        sonar_L_B = sonar_LEFT_BACK.ping_cm();
        if((sonar_L_B > DETECTED_CAR && sonar_L_B > MIN_DISTANCE) || (sonar_L_B < MIN_DISTANCE && sonar_L_B < DETECTED_CAR)){
          break;
        }

      }
    }
    
    if(sonar_L_S < DETECTED_CAR && sonar_L_S > MIN_DISTANCE && isAboveSpeed == 1){
      while(1){
        ledcWrite(BS_LEFT_LED_PWM, pwmBSLightOn);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
       

        sonar_L_S = sonar_LEFT_SIDE.ping_cm();
        if((sonar_L_S > DETECTED_CAR && sonar_L_S > MIN_DISTANCE) || (sonar_L_S < MIN_DISTANCE && sonar_L_S < DETECTED_CAR)){
          break;
        }
      }
    }    

    ledcWrite(BS_LEFT_LED_PWM, pwmBSLightOFF);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void BS_RIGHT_MANAGEMENT_SYSTEM(void *vpParam){

  while(1){


    int sonar_R_B = sonar_RIGHT_BACK.ping_cm();
    int sonar_R_S = sonar_RIGHT_SIDE.ping_cm();
   

    if(sonar_R_B < DETECTED_CAR && sonar_R_B > MIN_DISTANCE && isAboveSpeed == 1){
      while(1){
        ledcWrite(BS_RIGHT_LED_PWM, pwmBSLightOn);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
       

        sonar_R_B = sonar_RIGHT_BACK.ping_cm();

        if((sonar_R_B > DETECTED_CAR && sonar_R_B > MIN_DISTANCE) || (sonar_R_B < MIN_DISTANCE && sonar_R_B < DETECTED_CAR)){
          break;
        }
      }
    }

    if(sonar_R_S < DETECTED_CAR && sonar_R_S > MIN_DISTANCE && isAboveSpeed == 1){
      while(1){
        ledcWrite(BS_RIGHT_LED_PWM, pwmBSLightOn);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        

        sonar_R_S = sonar_RIGHT_SIDE.ping_cm();

        if((sonar_R_S > DETECTED_CAR && sonar_R_S > MIN_DISTANCE) || (sonar_R_S < MIN_DISTANCE && sonar_R_S < DETECTED_CAR)){
          break;
        }
      }
    }

    ledcWrite(BS_RIGHT_LED_PWM, pwmBSLightOFF);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

