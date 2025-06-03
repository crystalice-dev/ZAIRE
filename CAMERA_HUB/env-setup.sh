#! /bin/bash

echo '--ZAIRE HELMETS CAMERA REQ--'
sudo apt update
# Install build tools and dependencies
sudo apt-get install -y build-essential gcc git libopencv-dev libc6-dev ffmpeg fswebcam v4l-utils \
    cmake pkg-config \
    libjpeg-dev libtiff-dev libpng-dev \
    libavcodec-dev libavformat-dev libswscale-dev \
    libv4l-dev libxvidcore-dev libx264-dev \
    libgtk-3-dev libcanberra-gtk* \
    libatlas-base-dev gfortran python3-dev\
    g++ wget unzip\
    python3-dev libffi-dev build-essential\
    python3-pip\
    pip3 install esptool

# Instal OpenCV
sudo apt-get -y install libopencv-dev

echo '--ZAIRE HELMETS GPIOs REQ--'
sudo apt-get install -y git
git clone https://github.com/BPI-SINOVOIP/BPI-WiringPi.git -b BPI_M2P
cd BPI-WiringPi
chmod +x ./build
sudo ./build

echo '--ZAIRE HELMETS CAMERA AND GPIOs REQ COMPLETED--'

##use
##MAKE IT AUTO RUN -> move it to /usr/local/bin/ 
##sudo nano /etc/rc.local
##/usr/local/bin/my_program &
## ADD line above before exit 0
#ffmpeg -f v4l2 -input_format mjpeg -framerate 11.5 -video_size 320x240 -i /dev/video0 -c:v copy zaire_microvision_11_5_face2.mp4
#check camera fps  v4l2-ctl --device=/dev/video0 --list-formats-ext
## <------------- RESERVED --------------->
##gcc -o main main.c -lwiringPi -lm -lpthread -lrt -lcrypt
##g++ just_vid_main.cpp -o zaire_vision `pkg-config --cflags --libs opencv4`
#to be test
#fast
## enable UART2 & UART3 --> sudo armbian-config
: <<'END_COMMENT'
+-----+-----+---------+------+---+---Pi ---+---+------+---------+-----+-----+
| CPU | wPi |    Name   | Mode | V | Physical | V | Mode |   Name    | wPi | CPU |
+-----+-----+-----------+------+---+----++----+---+------+-----------+-----+-----+
|     |     |      3.3v |      |   |  1 || 2  |   |      | 5v        |     |     |
|  12 |   8 |     SDA.1 | ALT3 | 0 |  3 || 4  |   |      | 5V        |     |     |
|  11 |   9 |     SCL.1 | ALT3 | 0 |  5 || 6  |   |      | GND       |     |     |
|   6 |   7 |      PWM1 | ALT3 | 0 |  7 || 8  | 0 | ALT3 | UART3-TX  | 15  | 13  |
|     |     |       GND |      |   |  9 || 10 | 0 | ALT3 | UART3-RX  | 16  | 14  |
|   1 |   0 |  UART2-RX | ALT3 | 0 | 11 || 12 | 0 | ALT3 | UART3-CTS | 1   | 16  |
|   0 |   2 |  UART2-TX | ALT3 | 0 | 13 || 14 |   |      | GND       |     |     |
|   3 |   3 | UART2-CTS | ALT3 | 0 | 15 || 16 | 0 | ALT3 | UART3-RTS | 4   | 15  |
|     |     |      3.3v |      |   | 17 || 18 | 0 | ALT3 | GPIO.PC04 | 5   | 68  |
|  64 |  12 | SPI0_MOSI | ALT3 | 0 | 19 || 20 |   |      | GND       |     |     |
|  65 |  13 | SPI0_MISO | ALT3 | 0 | 21 || 22 | 0 | ALT3 | UART2-RTS | 6   | 2   |
|  66 |  14 |  SPI0_CLK | ALT3 | 0 | 23 || 24 | 0 | ALT3 | SPI0-CS   | 10  | 67  |
|     |     |       GND |      |   | 25 || 26 | 0 | ALT3 | GPIO.PL07 | 11  | 71  |
|  19 |  30 |     SDA.0 | ALT3 | 0 | 27 || 28 | 0 | ALT3 | SCL.0     | 31  | 18  |
|   7 |  21 | GPIO.PA07 | ALT3 | 0 | 29 || 30 |   |      | GND       |     |     |
|   8 |  22 | GPIO.PA08 | ALT3 | 0 | 31 || 32 | 0 | ALT3 | GPIO.PL02 | 26  | 354 |
|   9 |  23 | GPIO.PA09 | ALT3 | 0 | 33 || 34 |   |      | GND       |     |     |
|  10 |  24 | GPIO.PA10 | ALT3 | 0 | 35 || 36 | 0 | ALT3 | GPIO.PL04 | 27  | 356 |
|  17 |  25 | SPDIF-OUT | ALT3 | 0 | 37 || 38 | 0 | ALT3 | GPIO.PA21 | 28  | 21  |
|     |     |       GND |      |   | 39 || 40 | 0 | ALT3 | GPIO.PA20 | 29  | 20  |
+-----+-----+---------+------+---+---Pi ---+---+------+---------+-----+-----+
END_COMMENT

