#! /bin/bash

echo '--ZAIRE HELMETS CAMERA REQ--'
sudo apt update
sudo apt-get install -y libraspberrypi-bin
sudo apt-get install -y ffmpeg
echo '--ZAIRE HELMETS GPIOs REQ--'
sudo apt-get install -y git
git clone https://github.com/WiringPi/wiringPi.git
cd wiringPi
./build

echo '--ZAIRE HELMETS CAMERA AND GPIOs REQ COMPLETED--'
