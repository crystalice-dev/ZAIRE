| Target: ESP32-S2 N4R2| </br>
| Envmnt: ESP-IDF 5.3 | </br>
| vrsion: 3.0 | </br>
| Author: Yann Kabambi | </br>

# Zaire SYSTEM - S2 HUB

(See the README.md file in the upper level 'zaire-system' directory for more information about This whole project.)


The following contains a list of all the responsibilities this firmware has:

#### AUDIO:
* idf.py add-dependency "espressif/usb_device_uac=*"
* test: arecord -v -D hw:2,0 -f S16_LE -c 1 -r 16000 output3.wav

### DISPLAY:

* Create a directory called components in your main project directory.
* Change into the components directory.
* Run git clone https://github.com/mkfrey/u8g2-hal-esp-idf.git to bring in the latest copy of this library.
* Run git clone https://github.com/olikraus/u8g2.git to bring in a the latest copy of u8g2 library.
* for u8g2 cMakeLists.txt copy from -> https://github.com/olikraus/u8g2/blob/e52b1b52e6a8fbff193109bd4e9c72d9a1d32e4f/CMakeLists.txt


