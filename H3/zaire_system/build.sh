#! /bin/bash


echo '---BUILDING ZAIRE SYSTEM---'
gcc -o main main.c zaire_system.c gpio_config.c task_config.c uart_config.c -lwiringPi -lm -lpthread -lrt -lcrypt
echo '---DONE BUILDING ZAIRE SYSTEM---'
./main