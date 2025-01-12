#! /bin/bash

echo '--ZAIRE HELMETS CAMERA REQ--'
sudo apt update
sudo apt install -y libraspberrypi-bin
sudo apt install -y ffmpeg
echo '--ZAIRE HELMETS GPIOs REQ--'
git clone https://github.com/WiringPi/wiringPi.git
cd wiringPi
./build

echo '--ZAIRE HELMETS CAMERA AND GPIOs REQ COMPLETED--'
