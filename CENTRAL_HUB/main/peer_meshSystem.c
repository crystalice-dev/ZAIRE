#include "globalVar.h"



bool is_master_mode; // 1 - MASTER || 0 - SLAVE
bool isCompactOn; // Rather we are have an outside device in the Network to watch for ie Cardo, Sena, etc...
uint8_t walkie_address[6]; // Getting unit's walkie MAC addr from NVS -- Only if walkie_addr_nvs_registered = 1
uint8_t walkie_interject_number; // has to be 6
uint8_t number_paired_peers;
uint8_t number_paired_peers_walkie_addr_rec;
uint8_t bt_addr[6]; // Only if "isCompactOn" == 1
uint8_t peer_addresses[18][6]; // Up to 18
uint8_t peer_walkie_addresses[18][6]; // Up to 18


void peer_extract_slave_walkie_addr(void){ // Gather all slaves walkie

}  


void peer_received_slave_walkie_addr(void){ // Walkie addr from slaves

}