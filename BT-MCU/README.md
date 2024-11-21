# BLUETOOTH MCU FIRMWARE
updated: 11-21-2024 15:30🕞

(See the README.md file in the upper level for more information.)

This FIRMWARE uses esp-idf MASTER (5.5v at the time).</br>
This FIRMWARE has been tailored for ESP32 3.3V WROOM.</br>

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

