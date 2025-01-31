#include "./globalVar.h"

int serialPort;
char data[BUFFER_SIZE];
int  data_index = 0;
char buffer;

void central_uart_rec(char* str){
    int d = atoi(str); // convert str to int
    

}

void jdy_uart_snd(char* cmd){
    if(d == 0xAA){
        serialPuts(serialPort, "AT+NAMA HELLO WORLD\r\n");
    }
}

void* central_task(void* arg){

    while(1){
            if(serialDataAvail(serialPort)){
                    buffer = serialGetchar(serialPort);
                    if(buffer == '\n'){

                        central_uart_handler(data);
                        for(int i = 0; i < data_index; i++){
                            data[i] = ' ';
                        }
                        data_index = 0;
                        serialFlush(serialPort); // to prepare for next wave of data
                    }else{
                        data[data_index] = buffer;
                        data_index +=1;
                    }

            }
    }

    return NULL;

}

