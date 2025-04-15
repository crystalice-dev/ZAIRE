| Target: ALLWINNER H3| </br>
| Envmnt: armbian | </br>
| vrsion: 2.0 | </br>
| Author: Yann Kabambi | </br>

# Zaire Helmets - CAMERA hub unit

(See the README.md file in the upper level 'zaire_helmets' directory for more information about This whole project.)


The following contains a list of all the responsibilities this firmware has:

  * All camera functions (start/stop dashcam, take picture ie capture).
  * Process VISION software files (if enabled && depending on firmware version).
  * Read/Write data to sdCard ('CONFIG.zh' || 'CONFIG.zhf' depending on version).

    ### ENJOY - YANN KABAMBI !!
    01-19-2025 07:45🕞


#### CAMERA: 
* idf.py add-dependency "espressif/esp32-camera"
* idf.py add-dependency "espressif/usb_device_uvc=*"
#### AUDIO:
* idf.py add-dependency "espressif/usb_device_uac=*"
* test: arecord -v -D hw:2,0 -f S16_LE -c 1 -r 16000 output3.wav

