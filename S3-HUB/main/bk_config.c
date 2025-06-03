#include <globalVar.h>

#if AUDIO_CHIP == AUDIO_CHIP_BK3266

bk_target_stage_t bk_target_stage = NORMAL;
bk_connection_mode_t bk_connection_mode = DISCONNECTED;
uint8_t bk_volume = 16;

void bk_init(void){
    bk_set_device_volume(bk_volume);
    bk_phone_en();
}

void bk_set_device_name(const char *name){
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "AT+NAMA %s\r\n", name);
    bk_uart_snd(cmd);
    bk_target_stage = SET_NAME;
}

void bk_get_device_name(void){

}

void bk_set_device_volume(uint8_t vol){
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "AT+VOLUME%d\r\n", vol);
    bk_uart_snd(cmd);
    bk_target_stage = SET_VOL;
}

void bk_get_player_status(void){

}

void bk_get_connection_status(void){

}

void bk_next_song(void){
    bk_uart_snd(BK_NEXT_SONG);
}

void bk_prev_song(void){
    bk_uart_snd(BK_PREV_SONG);
}

void bk_vol_up(void){
    if(bk_volume == 0){
        bk_volume = 8;
    }else{
        bk_volume += 1;
    }

    if(bk_volume < 17){
        bk_set_device_volume(bk_volume);
        bk_target_stage = SET_SONG;
    }else{
        bk_volume = 16;
        bk_set_device_volume(bk_volume);
        bk_notification();
    }
}

void bk_vol_down(void){
    bk_volume -= 1;
    if(bk_volume  > 7){
        bk_set_device_volume(bk_volume);
        bk_target_stage = SET_SONG;
    }else{
        bk_volume = 0;
        bk_set_device_volume(bk_volume); // mute
        bk_notification();
    }
}

void bk_key(void){

}

void bk_disconnect(void){

}

void bk_phone_en(void){
    bk_uart_snd(BK_EN_PHONE);
}

void bk_notification(void){
    bk_uart_snd(BK_NOTIFICATION);
}


#endif