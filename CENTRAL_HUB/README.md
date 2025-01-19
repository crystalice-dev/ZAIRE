| Target: ESP32-S3| </br>
| Envmnt: ESP-IDF 5.5.0 | </br>
| vrsion: 5.0 | </br>
| Author: Yann Kabambi  | </br>

# zaire helmets - central hub unit

(See the README.md file in the upper level 'zaire_helmets' directory for more information about This whole project.)

The following contians a list of all the responsibilities this firmware has:

* All camera functions (start/stop dashcam, take picture ie capture).
* All UART communication [central data process for BM83 - walkie - (RPi depending on firmware version) ].
* Blindspot monitoring (trigger led pin to walkie).
* Connect to other zaire helmet during 'MESH' connection.
* Check BATTERY LEVEL -- MAX17048G+T10.
* Check Temp -- AHT20_C2757850.
* Remote connection && communication.
* Sends mac addr of helmets in the 'MESH'.
* Share helmet's walkie mac address for walkie-talkie.



#### ENJOY - YANN KABAMBI !!


