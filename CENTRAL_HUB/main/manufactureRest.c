#include "globalVar.h"



bool manufactureReset(uint8_t code){

    nvs_write(walkie_addr_nvs_registered, WALKIE_ADDR_KEY, 0); // Rest walkie addr

    return 0;

}