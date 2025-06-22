#include "globalVar.h"


pthread_t host_Pthread;
pthread_t walkie_Pthread;
pthread_t onBoardLED_Pthread;

onBoardLED_t onBoardLED = NONE;

int init_pthread(void){

    if(pthread_create(&walkie_Pthread,NULL,walkie_uart_task, NULL) != ZAIRE_OK){
        printf("walkie_uart_task failed init\n");
        return ZAIRE_FAIL;
    }

    if(pthread_create(&host_Pthread,NULL,host_uart_task, NULL) != ZAIRE_OK){
        printf("host_uart_task failed init\n");
        return ZAIRE_FAIL;
    }

    if(pthread_create(&onBoardLED_Pthread, NULL, onBoard_LED_task, NULL) != ZAIRE_OK){
        printf("onBoard_LED_task failed init\n");
        return ZAIRE_FAIL;
    }

    return ZAIRE_OK;
}

int start_pthread(void){

    if(pthread_join(walkie_Pthread, NULL) != ZAIRE_OK){
        printf("walkie_uart_task failed start\n");
        return ZAIRE_FAIL;
    }

    if(pthread_join(host_Pthread, NULL) != ZAIRE_OK){

        printf("host_uart_task failed start\n");
        return ZAIRE_FAIL;
    }

    if(pthread_join(onBoardLED_Pthread, NULL) != ZAIRE_OK){
        printf("host_uart_task failed start\n");
        return ZAIRE_FAIL;
    }

    return ZAIRE_OK;

}

void* walkie_uart_task(void* arg) {
    char buffer[BUFFER_SIZE];
    int buffer_index = 0;

    while (1) {
        // Only check serial if there's data available
        while (serialDataAvail(walkie_serialPort) > 0) {
            char data = serialGetchar(walkie_serialPort);

            if (data == '\r') continue; // skip carriage return

            if (data != '\n' && buffer_index < BUFFER_SIZE - 1) {
                buffer[buffer_index++] = data;
            } else {
                buffer[buffer_index] = '\0';

                if (buffer_index > 0) {
                    printf("walkie: %s\n", buffer);
                    fflush(stdout);
                }

                buffer_index = 0; // reset for next message
                memset(buffer, 0, BUFFER_SIZE); // optional: zero out the buffer
            }
        }

        // Avoid busy-waiting
        usleep(10); // sleep 1ms
    }

    return NULL;
}

void* host_uart_task(void* arg) {
    char buffer[BUFFER_SIZE];
    int buffer_index = 0;

    while (1) {
        // Only check serial if there's data available
        while (serialDataAvail(host_serialPort) > 0) {
            char data = serialGetchar(host_serialPort);

            if (data == '\r') continue; // skip carriage return

            if (data != '\n' && buffer_index < BUFFER_SIZE - 1) {
                buffer[buffer_index++] = data;
            } else {
                buffer[buffer_index] = '\0';

                if (buffer_index > 0) {
                    host_uart_rec(buffer);
                    fflush(stdout);
                }

                buffer_index = 0; // reset for next message
                memset(buffer, 0, BUFFER_SIZE); // optional: zero out the buffer
            }
        }

        // Avoid busy-waiting
        usleep(10); // sleep 1ms
    }

    return NULL;
}


void* onBoard_LED_task(void* arg){
    while(1){

        switch(onBoardLED){

            case NONE:
                digitalWrite(ON_BOARD_LED, LOW);
                break;

            case STANDBY:
                digitalWrite(ON_BOARD_LED, HIGH);
		digitalWrite(ESP_RST, LOW);
                digitalWrite(ESP_BOOT0, HIGH);
		break;

            case FLASHING:
		digitalWrite(ESP_RST, HIGH);
		digitalWrite(ESP_BOOT0, LOW);
                digitalWrite(ON_BOARD_LED, HIGH);
                delay(50);
                digitalWrite(ON_BOARD_LED, LOW);
                delay(40);
		break;
        }

        usleep(10);
    }
}
