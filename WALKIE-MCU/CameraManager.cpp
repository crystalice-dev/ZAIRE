#include <Arduino.h>
#include "globalVar.h"


String Date = "";
String Time = "";
bool CAMERA_AUTO_STATUS = false;
bool isDashCamOn = false;
bool isCaptureOn = false;
String speed = "N/A";
String filePath = "";
unsigned long frame = 0;
bool readyToCreateFolder = true; // local -- will change to false on start

bool InitSDCard(){

  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) {
    return false;
  }
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
      
      return false;
  }

  return true;

}


bool InitCamera(){

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // for larger pre-allocated frame buffer.
  if(psramFound()){
    config.jpeg_quality = 10;
    config.fb_count = 2;
    config.grab_mode = CAMERA_GRAB_LATEST;
  } else {
    // Limit the frame size when PSRAM is not available
    config.frame_size = FRAMESIZE_SVGA;
    config.fb_location = CAMERA_FB_IN_DRAM;
  }

  // Initialize the camera
  if (esp_camera_init(&config) != ESP_OK) {
    
    return false;
  }

  return true;

}

// void DashCam(){
  
  // for(int i = 0 ; i < 100; i++){
    
  //   //appendFile(SD_MMC, (String("/DashCam/") + Date + "/GaugeWatch.txt").c_str(), (String("Speed: ") + x + "\n").c_str()); 
   
  // }

//   while(!isCaptureOn){

//     delay(1);

//     // Capture a photo
//     camera_fb_t *fb = esp_camera_fb_get();
//     if (!fb) {
//       Serial.println("Camera capture failed");
//       return;
//     }

//     // Generate a unique filename for each photo
//     String path = (String("/DashCam/") + filePath + "/frame-").c_str() + String(frame) + ".jpg";
    
//     if(GPS_Speed > -1 ){
//       speed = String(GPS_Speed).c_str();
//     }else{
//       speed = "N/A";
//     }

//     // Save to SD card
//     File file = SD_MMC.open(path.c_str(), FILE_WRITE);
//     appendFile(SD_MMC, (String("/DashCam/") + filePath + "/GaugeWatch.txt").c_str(), String(speed + "\n").c_str()); 
//     if (!file) {
//       Serial.println("Failed to open file in write mode");
//     } else {
//       file.write(fb->buf, fb->len);  // Write the photo to the file
    
//     }
//     file.close();

//     // Return the frame buffer back to the driver
//     esp_camera_fb_return(fb);
//     frame +=1; //add frame

//   }

   

// }


void buzzerCaptureSoundSuccess(){
  ledcWriteTone(BUZZER_CHANNEL, 5000);
  delay(50);
  ledcWriteTone(BUZZER_CHANNEL, 0);
  delay(50);
  ledcWriteTone(BUZZER_CHANNEL, 5000);
  delay(50);
  ledcWriteTone(BUZZER_CHANNEL, 0);
  delay(50);
}

void buzzerCaptureSoundFailed(){
  ledcWriteTone(BUZZER_CHANNEL, 5000);
  delay(250);
  ledcWriteTone(BUZZER_CHANNEL, 0);
}


// void CapturePhoto(){

//   bool wasDashOn = false;
//   isCaptureOn = true;
//   if(isDashCamOn){
//     wasDashOn = true;
//   }else{
//     wasDashOn = false;
//   }

//   isDashCamOn = false;
  
//   // Capture a photo
//     camera_fb_t *fb = esp_camera_fb_get();
//     if (!fb) {
//       Serial.println("Camera capture failed");
//       return;
//     }

//     String path = "/Photos/Picture-" + String(millis()) + ".jpg";
//     File file = SD_MMC.open(path.c_str(), FILE_WRITE);

//     if(wasDashOn){
//       if(GPS_Speed > -1 ){
//         speed = String(GPS_Speed).c_str();
//       }else{
//         speed = "N/A";
//       }
//       String framePath = (String("/DashCam/") + filePath + "/frame-").c_str() + String(frame) + ".jpg";
//       File frameFile = SD_MMC.open(framePath.c_str(), FILE_WRITE);
//       frameFile.write(fb->buf, fb->len);
//       appendFile(SD_MMC, (String("/DashCam/") + filePath + "/GaugeWatch.txt").c_str(), String(speed + "\n").c_str()); 
//       frame +=1;
//       Serial.println(frame);
//     }

//     if (!file) {
//       buzzerCaptureSoundFailed();
//     } else {
//       file.write(fb->buf, fb->len);  // Write the photo to the file
//       buzzerCaptureSoundSuccess();
//     }
//     file.close();

//     // Return the frame buffer back to the driver
//     esp_camera_fb_return(fb);

//     vTaskDelay(1000 / portTICK_PERIOD_MS);;

//     if(wasDashOn){
//       isDashCamOn = true;
//     }
//     isCaptureOn = false;

// }


void Camera_SDCardManager(void *vpParam){
  while(1){
    
    if((readyToCreateFolder == true && Date != "" && Time != "") && isCameraActive == true){
      String current = serialData.substring(5,19);
      String filePathDate = current.substring(0,2) + "-" + current.substring(2,4) + "-" + current.substring(4,8);
      String filePathTime = current.substring(8,10) + "-" + current.substring(10,12) + "-" + current.substring(12,14); 
      filePath = String(filePathDate + "/" + filePathTime).c_str();
      createDir(SD_MMC, "/DashCam");
      createDir(SD_MMC, "/Photos");
      createDir(SD_MMC, (String("/DashCam/") + filePathDate).c_str());
      createDir(SD_MMC, (String("/DashCam/") + filePathDate + "/" + filePathTime).c_str());
      writeFile(SD_MMC, (String("/DashCam/") + filePath + "/GaugeWatch.txt").c_str(), "SPEED AND TIME RECORD: \n ");

      if(CAMERA_AUTO_STATUS){ // found in BT user settings
        isDashCamOn = true;
      }else{
        isDashCamOn = false;
      }

      readyToCreateFolder = false; // sets every off for camera to start
    }

    if(isDashCamOn && !readyToCreateFolder){
      //DashCam();
    }
  
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
