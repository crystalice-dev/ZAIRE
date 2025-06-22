#include "globalVar.h"


uint8_t isFirstBoot = 0;

int zaire_system_setup(void){
	int err;
	char command[512];
//	snprintf(command, sizeof(command), "nmcli radio wifi off");
//	err = system(command);
//	if(err != ZAIRE_OK)return ZAIRE_FAIL;

	return ZAIRE_OK;
}


int flash_ESP_FIRMWARE(void){
	char buffer[256];
	uint8_t line = 0;
	uint8_t boot = 0;
	onBoardLED = STANDBY;
	FILE *file = fopen("engine.zcfg","r+");

	if(file == NULL){
		perror("Error opening file\n");
		return ZAIRE_FAIL;
	}

	while(fgets(buffer, sizeof(buffer), file) != NULL){
		if(line == 3){
			boot = atoi(&buffer[12]);
			break;
		}
		line +=1;

	}

	if(boot==1){
		printf("FLASHING\n");
		onBoardLED = FLASHING;
		flash_BOOT_ESP();
		//Write to file '#FRIST_BOOT=0'
	}else{
		fclose(file);
	}


	onBoardLED = NONE;

	return ZAIRE_OK;
}

void flash_FLASH_ESP_HOST_FIRMWARE(void){
	int flash_status = system("./HOST_FIRMWARE/flash.sh");
	if(flash_status != ZAIRE_OK){
		system("./HOST_FIRMWARE/flash.sh"); //Retry in case of fail
	}
}

void flash_FLASH_ESP_WALKIE_FIRMWARE(void){
	int flash_status = system("./WALKIE_FIRMWARE/flash.sh");
	if(flash_status != ZAIRE_OK){
		system("./WALKIE_FIRMWARE/flash.sh"); //Retry in case of fail
	}

}

void flash_RST_ESP(void){
	digitalWrite(ESP_BOOT0, HIGH);
	digitalWrite(ESP_RST, LOW);
	delay(100);
	digitalWrite(ESP_RST, HIGH);
}

void flash_BOOT_ESP(void){
	digitalWrite(ESP_BOOT0, LOW);
	digitalWrite(ESP_RST, LOW);
	delay(100);
	digitalWrite(ESP_RST, HIGH);

	// KEEP ESP_BOOT0 LOW while flashing:
	flash_FLASH_ESP_HOST_FIRMWARE();
	flash_FLASH_ESP_WALKIE_FIRMWARE();

	digitalWrite(ESP_BOOT0, HIGH); // finally release

	flash_RST_ESP();
}

