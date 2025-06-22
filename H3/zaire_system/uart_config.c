#include "globalVar.h"



int host_serialPort;
int walkie_serialPort;


int init_uart(void){

    if((host_serialPort = serialOpen(HOST_PORT, HOST_BAUD)) < ZAIRE_OK){
        printf("HOST\n");
        return ZAIRE_FAIL;
    }

    if((walkie_serialPort = serialOpen(WALKIE_PORT, WALKIE_BAUD)) < ZAIRE_OK){
        printf("WALKIE\n");
        return ZAIRE_FAIL;
    }

    return ZAIRE_OK;
}

void host_uart_rec(char* str){

	if(str[0] == 'H'){
		if(http_server_running == 0){
			get_dns_ssid_bssid(str);
			delay(200); // time for dns to start
			int err = start_http_server();
			delay(200);
			if(err == ZAIRE_FAIL)host_uart_snd("D|R\n"); //Re-try connection
		}else{
			stop_http_server();
			delay(200);
		}
	}else{
		//printf("HOST: %s\n", str);
	}
}

void host_uart_snd(char* str){
	printf("Sending: %s\n", str);
    	serialPuts(host_serialPort, str);
    	delay(100);
}


void walkie_uart_rec(char* str){

    printf("%s\n", str);

}

void walkie_uart_snd(char* str){
    serialPuts(walkie_serialPort, str);
    delay(100);
}
