| Target: ESP32| </br>
| Envmnt: ARDUINO 2.3.4| </br>
| vrsion: 5.0 | </br>
| Author: Yann Kabambi | </br>

# zaire helmets - WALKIE hub unit
#### IMPORTANT: ARDUINO IDE -> BOARD MANAGER -> ESP32 by Espressif System VERSION *2.0.17*
###### ANY VERSION ABOVE THAT WILL NOT WORK!!!
(See the README.md file in the upper level 'zaire_helmets' directory for more information about This whole project.)

The following contains a list of all the responsibilities this firmware has:

* All camera functions (start/stop dashcam, take picture ie capture).
* All UART communication [central data process for BM83 - walkie - (RPi depending on firmware version) ].
* Blindspot monitoring (trigger led pin to walkie).
* Connect to other zaire helmet during 'MESH' connection.
* Check BATTERY LEVEL -- MAX17048G+T10.
* Check Temp -- AHT20_C2757850.
* Remote connection && communication.
* Sends mac addr of helmets in the 'MESH'.
* Share helmet's walkie mac address for walkie-talkie.

### ENJOY - YANN KABAMBI !!
01-19-2025 07:45🕞 
