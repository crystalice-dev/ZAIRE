#include "globalVar.h"


pthread_t host_Pthread;
pthread_t walkie_Pthread;

int init_pthread(void){

    if(pthread_create(&walkie_Pthread,NULL,walkie_uart_task, NULL) != ZAIRE_OK){
        printf("walkie_uart_task failed init\n");
        return ZAIRE_FAIL;
    }

    if(pthread_create(&host_Pthread,NULL,host_uart_task, NULL) != ZAIRE_OK){
        printf("host_uart_task failed init\n");
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
                    printf("Received: %s\n", buffer);
                    fflush(stdout);
                }

                buffer_index = 0; // reset for next message
                memset(buffer, 0, BUFFER_SIZE); // optional: zero out the buffer
            }
        }

        // Avoid busy-waiting
        usleep(1000); // sleep 1ms

        walkie_uart_snd("HELLO from BPI \n\r");
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
                    walkie_uart_rec(buffer);
                    fflush(stdout);
                }

                buffer_index = 0; // reset for next message
                memset(buffer, 0, BUFFER_SIZE); // optional: zero out the buffer
            }
        }

        // Avoid busy-waiting
        usleep(1000); // sleep 1ms
    }

    return NULL;
}