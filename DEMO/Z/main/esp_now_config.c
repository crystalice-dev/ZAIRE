#include "globalVar.h"


bool mesh_system_active = 0;
walkie_pairing_mode_t walkie_pairing_mode = NONE;
uint8_t device_sta_mac[6];
uint8_t peer_addresses[8][6];
uint8_t temp_peer_addr[6];
uint8_t number_paired_peers = 1; // 1 is us
uint8_t new_peers  = 0;
