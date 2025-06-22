#include "globalVar.h"




int main(){

	if(zaire_system_setup() != ZAIRE_OK)return ZAIRE_FAIL;

    	if(wiringPiSetup() < 0)return -ZAIRE_FAIL;

    	init_gpio();

    	if(init_pthread() != ZAIRE_OK)return ZAIRE_FAIL;

//   	flash_ESP_FIRMWARE();

    	//Only after checking if we have already flashed ESPs firmwares
    	if(init_uart() != ZAIRE_OK)return ZAIRE_FAIL;

    	delay(200); //Delay for all floating pthread

	printf("Done\n");

    	if(start_pthread() != ZAIRE_OK)return ZAIRE_FAIL; //LAST ON <- IMPORTANT

    	return 0;
}
