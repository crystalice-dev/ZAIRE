#include <globalVar.h>


esp_err_t zaire_system_check(){
    //init_spiffs();
    // NVS_init();
    
    //WALKIE
    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());

    //GPIO
    ESP_ERROR_CHECK(gpio_pin_init());
    
    //i2c_init();
   // uart_init();
   
   #ifdef WALKIE_INCLUDED
        I2SInit();
    #endif

   //UART
    ESP_ERROR_CHECK(uart_init());

    //USB CAMERA
    // ESP_ERROR_CHECK(camera_init());
    // ESP_ERROR_CHECK(usb_init());

    //AUDIO CHIP
    #if AUDIO_CHIP == AUDIO_CHIP_BK3266
        bk_init();
    #endif

    return ESP_OK;
}

#if AUDIO_CHIP != AUDIO_CHIP_NONE
    void audio_chip_uart_handler(uint8_t code){
        switch (code){
            case AUDIO_PLAYER_NEXT:
                bk_next_song();
                printf("N\n");
                break;
            case AUDIO_PLAYER_PREV:
                bk_prev_song();
                printf("P\n");
                break;
            case AUDIO_PLAYER_VOL_UP:
                bk_vol_up();
                printf("U\n");
                break;
            case AUDIO_PLAYER_VOL_DWN:
                bk_vol_down();
                printf("D\n");
                break;
            default:
                break;
        } 
    }
#endif