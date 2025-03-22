#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define GPIO        8

int serial_port;
char buffer[BUFFER_SIZE];
int buffer_index = 0;
char dat;

void* sender(void *vpParam) {
    while (1) {
        serialPuts(serial_port, "Hello ESP32\n");
        delay(1000);
    }
    return NULL;
}

void* receiver(void *vpParam) {
    while (1) {
        if (serialDataAvail(serial_port)) {
            dat = serialGetchar(serial_port);
            if (dat != '\n' && buffer_index < BUFFER_SIZE - 1) {
                buffer[buffer_index++] = dat;
            } else {
                buffer[buffer_index] = '\0';
                printf("Received: %s\n", buffer);
                fflush(stdout);
                buffer_index = 0;
            }
        }
    }
    return NULL;
}

void* readGPIO(void *vpParam) {
    while (1) {
        printf("GPIO %i: %i\n", GPIO, digitalRead(GPIO));
        fflush(stdout);
        delay(1000);
    }
    return NULL;
}

int main() {
    if (wiringPiSetup() == -1) {
        printf("Failed to init wiringPi\n");
        return 1;
    }

    pinMode(GPIO, INPUT);
    memset(buffer, 0, sizeof(buffer));  // Init buffer cleanly

    if ((serial_port = serialOpen("/dev/ttyS3", 9600)) < 0) {
        printf("Could not open /dev/ttyS3\n");
        return 1;
    }

    pthread_t senderThread, receiverThread, readGpioThread;

    if (pthread_create(&senderThread, NULL, sender, NULL) != 0) {
        perror("Failed to create sender thread");
        return 1;
    }

    if (pthread_create(&receiverThread, NULL, receiver, NULL) != 0) {
        perror("Failed to create receiver thread");
        return 1;
    }

    if (pthread_create(&readGpioThread, NULL, readGPIO, NULL) != 0) {
        perror("Failed to create readGPIO thread");
        return 1;
    }

    pthread_join(senderThread, NULL);
    pthread_join(receiverThread, NULL);
    pthread_join(readGpioThread, NULL);

    return 0;
}
