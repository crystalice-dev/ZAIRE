# WALKIE MCU FIRMWARE

*    Author  : YANN KABAMBI
*    Title   : ZAIRE_HELMET_WALKIE_MCU_FIRMWARE
*    Version : 2.0
*    Describ : WALKIE - BLIND SPOT MONITORE - GPS - BH1750 - TEMP
*    walkie  : zuoyi001 -> https://github.com/zuoyi001/ESP32_walkie_talkie

updated: 11-21-2024 15:30🕞

(See the README.md file in the upper level for more information.)

This FIRMWARE uses ARDUINO FRAMEWORK (2.2.3 at the time).</br>
This FIRMWARE has been tailored for ESP32 [ESP32DEV MODULE] (MUST BE 2.0v > Version < 3.0v).

## FIRMWARE contents
*BLUETOOTH CLASSIC -> A2DP with AVR Controller for AUDIO CONTROL. (PLAY/PAUSE; NEXT; PREVIOUS).</br>
*BLUETOOTH HFP_HF  -> Phone Call handler</br>
*BLUETOOTH BLE -> Device and Mobile App handler.</br>
*RTC -> uses UART to set/get local time from the onBoard UART. (time is set as soon as Mobile phone app communicates with the device).</br>

The **FIRMWARE** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).</br>

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```


