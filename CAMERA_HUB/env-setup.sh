#! /bin/bash

echo '--ZAIRE HELMETS CAMERA REQ--'
sudo apt update
sudo apt install build-essential
sudo atp-get install -y gcc
sudo apt-get install -y libraspberrypi-bin
sudo apt install libc6-dev
sudo apt-get install -y ffmpeg
echo '--ZAIRE HELMETS GPIOs REQ--'
sudo apt-get install -y git
git clone https://github.com/WiringPi/wiringPi.git
cd wiringPi
./build

echo '--ZAIRE HELMETS CAMERA AND GPIOs REQ COMPLETED--'

##use
##MAKE IT AUTO RUN -> move it to /usr/local/bin/ 
##sudo nano /etc/rc.local
##/usr/local/bin/my_program &
## ADD line above before exit 0
#ffmpeg -f v4l2 -framerate 25 -video_size 640x480  -i /dev/video0 -c:v libx264 -preset veryfast -f mp4 ~/video.mp4
#to be test
#fast