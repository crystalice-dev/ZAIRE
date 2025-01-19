#include "globalVar.h"



bool is_master_mode; // 1 - MASTER || 0 - SLAVE
bool isCompactOn; // Rather we are have an outside device in the Network to watch for ie Cardo, Sena, etc...
uint8_t walkie_address[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t walkie_interject_number = 0;
uint8_t bt_addr[6]; // Only if "isCompactOn" == 1

uint8_t number_paired_peers_walkie_addr_rec = 0;
uint8_t number_paired_peers = 0; 
uint8_t peer_addresses[18][6];
uint8_t peer_walkie_addresses[18][6];


void peer_extract_slave_walkie_addr(void){
    uint8_t data = GET_WALKIE_ADDR;
    for(int i = 0; i < number_paired_peers; i++){
        esp_now_send(peer_addresses[i], &data, 1);
        vTaskDelay(pdMS_TO_TICKS(50));
    }

}

void peer_received_slave_walkie_addr(void){

}


