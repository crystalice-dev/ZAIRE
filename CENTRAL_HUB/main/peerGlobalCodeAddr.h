#ifndef PEER_GLOBAL_CODE_ADDR
#define PEER_GLOBAL_CODE_ADD


#define RESTARTING_DEVICE           0xFA // Alert system we are restaring -- system check failed -- esp_now now init properly -- etc
#define BREAK_WIFI_BROADCAST        0xFE // On esp_now connect -- slave close wifi signal and add master's mac addr to its peer

#define OPEN_ADDR_INSERT            0xE1 // Alert for incoming peer's walkie mac addr
#define CLOSE_ADDR_INSERT           0xE0 // Alert inserted mac addr ends

#define GET_WALKIE_ADDR             0xA1 // Request from master to slave or to unit's walkie core
#define SET_WALKIE_ADDR             0xB1 // Request to set walkie_address to nvs_bob --
#define GET_BT_UNIT_ADDR            0xA2 // Request from master to unit's BT core

#define CLOSING_PAIRING_MODE        0XC0 // CLOSING PAIRING MODE -- MASTER || SLAVE
#define ENTERING_PAIRING_MODE       0xC1 // ENTERING PAIRING MODE -- MASTER || SLAVE

#define READ_DATA_RAW               0xFC // Request UART receiver to read data raw not uint8_t

#define CLOSE_SETTING_PORT          0xD0 // Request Walkie to close settings port -- wifi -- walkie mesh on
#define OPEN_SETTING_PORT           0xD1 // Request Walkie to open settings port -- wifi -- walkie mesh off
#define OPENED_SETTING_PORT         0xD2 // Respond To Central settings port opened -- wifi -- walkie mesh off
#define CLOSED_SETTING_PORT         0xD3 // Respond To Central settings port closed -- wifi -- walkie mesh  on

#endif