#include "globalVar.h"




int main()
{
    //init wiringPisudo 
    if(wiringPiSetup() < 0){
        printf("wiringPi faile to Init\n");
        return -ZAIRE_FAIL;
    }


    init_gpio();
    
    if(init_uart() != ZAIRE_OK){
        printf("UART failed to init\n");
        return ZAIRE_FAIL;
    }

    if(init_pthread() != ZAIRE_OK){
        printf("init_pthread failed\n");
        return ZAIRE_FAIL;
    }


    if(start_pthread() != ZAIRE_OK){
        printf("start_pthread failed \n");
        return ZAIRE_FAIL;
    }
    
   

    return 0;
}