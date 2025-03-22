#! /bin/bash

echo '--ZAIRE HELMETS CAMERA REQ--'
sudo apt-apt update
sudo apt-get -y upgrade
# Install build tools and dependencies
sudo apt install -y build-essential gcc libopencv-dev libc6-dev ffmpeg fswebcam v4l-utils 
 
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
#ffmpeg -f v4l2 -framerate 25 -video_size 640x480  -i /dev/video0 -c:v libx264 -preset veryfast -f mp4 ~/video.mp4
## <------------- RESERVED --------------->
##gcc -o main main.c -lwiringPi -lm -lpthread -lrt -lcrypt
#to be test
#fast
