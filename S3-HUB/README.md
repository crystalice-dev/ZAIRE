| Target: ESP32-S3 N16R8| </br>
| Envmnt: ESP-IDF 5.3 | </br>
| vrsion: 3.0 | </br>
| Author: Yann Kabambi | </br>

# Zaire SYSTEM - S2 HUB

(See the README.md file in the upper level 'zaire-system' directory for more information about This whole project.)


The following contains a list of all the responsibilities this firmware has:

#### AUDIO:
* idf.py add-dependency "espressif/usb_device_uac=*"
* test: arecord -v -D hw:2,0 -f S16_LE -c 1 -r 16000 output3.wav

