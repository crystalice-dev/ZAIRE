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
#ffmpeg -f v4l2 -framerate 25 -video_size 640x480  -i /dev/video0 -c:v libx264 -preset veryfast -f mp4 ~/Desktop/video.mp4

