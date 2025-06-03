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

// void host_uart_rec(char* str);
// void host_uart_snd(char* str);
void walkie_uart_rec(char* str){

    printf("%s\n", str);

}

void walkie_uart_snd(char* str){
    serialPuts(walkie_serialPort, str);
    delay(100);
}