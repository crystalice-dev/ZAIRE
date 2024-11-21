#include <Arduino.h>
#include "globalVar.h"



// Call outs
bool sendOver=1;
bool recOver=0;
bool speakOut;



void WalkieTalkie(void *vpParam){

  while(1){

    if(!digitalRead(WALKIE_PIN))
      {
        speakOut=0;
        digitalWrite(LED,HIGH);
        int samples_read = I2Sread(samples_16bit,128);
        covert_bit(samples_16bit,samples_8bit,samples_read);
        sendData(samples_8bit,samples_read);
      }
    else
    {
      delay(28);
      speakOut=1;
      if(recOver)
      {
        recOver=0;
        if(digitalRead(LED))
        {
            digitalWrite(LED,LOW);
        }
        else
        {
            digitalWrite(LED,HIGH);
        }
      }
      else
      {
        digitalWrite(LED,LOW);
        i2s_zero_dma_buffer(SPK_I2S_PORT);
      }
    }


  }

}
