#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


//DEVICE TYPES
#define DEVICE_TYPE_SKI_GOGGLES     (0)
#define DEVICE_TYPE_BICYCLE_HELMET  (1)
#define DEVICE_TYPE_MOTOR_HELMET    (2)
#define DEVICE_TYPE        DEVICE_TYPE_BICYCLE_HELMET// Must come before zaire_system.h -- avoid loop defination
#include "zaire_system.h"


//GPIO BOARD ASSIGN
void init_gpio();

//HTTP SERVER
#define HTTP_FOLDER_PATH	"~/storage"
extern char local_ip[INET_ADDRSTRLEN];
extern int http_server_preConnected;
extern int http_server_running;
extern char dns_server_ssid[256];
extern char dns_server_bssid[256];
int start_http_server(void);
int stop_http_server(void);
void get_local_ip(void);
void get_dns_ssid_bssid(char* id);

//uart
#define HOST_PORT               "/dev/ttyS3"
#define WALKIE_PORT             "/dev/ttyS2"
#define HOST_BAUD               115200
#define WALKIE_BAUD             1200
#define BUFFER_SIZE             1024
extern int host_serialPort;
extern int walkie_serialPort;
int init_uart(void);
void host_uart_rec(char* str);
void host_uart_snd(char* str);
void walkie_uart_rec(char* str);
void walkie_uart_snd(char* str);
void jdy_uart_snd(char* cmd);

//pthread tasks
extern pthread_t host_Pthread;
extern pthread_t walkie_Pthread;
int init_pthread(void);
int start_pthread(void);
void* gpio_task(void* arg);
void* walkie_uart_task(void* arg);
void* host_uart_task(void* arg);
void* camera_task(void* arg);
void* onBoard_LED_task(void* arg);

#endif
