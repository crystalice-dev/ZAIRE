#include <globalVar.h>

#define I2C_1_SDA           GPIO_NUM_4
#define I2C_1_SCL           GPIO_NUM_5

u8g2_t display;
bool display_special_on = true;
bool display_en = HIGH;
int display_timer = 3000;
display_target_t display_target = DISPLAY_MAIN_UI;
display_button_target_t display_button_target = 1;

esp_err_t init_display(){

    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.bus.i2c.sda = ACC_I2C_SDA_PIN;
    u8g2_esp32_hal.bus.i2c.scl = ACC_I2C_SCL_PIN;
    u8g2_esp32_hal_init(u8g2_esp32_hal);

    u8g2_Setup_ssd1306_i2c_128x32_univision_f(
        &display, U8G2_R0,
        u8g2_esp32_i2c_byte_cb,
        u8g2_esp32_gpio_and_delay_cb
    );
    
    u8x8_SetI2CAddress(&display.u8x8, 0x3C << 1);  // safer way to write 0x78
    u8g2_InitDisplay(&display);
    u8g2_SetPowerSave(&display, 0);

    display_welcome_animation();
    vTaskDelay(pdMS_TO_TICKS(750)); // Hold display text 
    display_target = DISPLAY_MAIN_UI;

    return ZAIRE_OK;
}

void display_welcome_animation(void){
    const char *word = "ZAIRE";
    int len = strlen(word);

    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenB18_tr);

    for (int i = 0; i < len; i++) {
        char partial[6] = {0}; // 5 letters + null terminator
        strncpy(partial, word, i + 1);  // Copy first i+1 letters
        u8g2_ClearBuffer(&display);     // Clear previous
        u8g2_DrawStr(&display, 20, 25, partial);  // Draw partial word
        u8g2_SendBuffer(&display);      // Send to display
        vTaskDelay(pdMS_TO_TICKS(100)); //100ms
    }

    //vTaskDelay(pdMS_TO_TICKS(200)); //


    // int bar_x = 3;
    // int bar_y = 30;
    // int bar_width = 120;
    // int bar_height = 3;

    // for (int w = 0; w <= bar_width; w += 5) {
    //     u8g2_DrawBox(&display, bar_x, bar_y, w, bar_height);
    //     u8g2_SendBuffer(&display);
    //     vTaskDelay(pdMS_TO_TICKS(0.5));
    // }
}

void display_quick_show_menu(void){

    switch (display_button_target)
    {
    case DISPLAY_OFF:
        display_target = DISPLAY_OFF;
        break;
    case DISPLAY_MAIN:
        display_target = DISPLAY_MAIN_UI;
        break;
    case DISPLAY_SETTINGS:
        display_target = DISPLAY_SHOW_DNS_SETTING;
        break;
    case DISPLAY_BLUETOOTH:
        display_target = DISPLAY_SHOW_BK3266_BLUETOOTH;
        break;
    case DISPLAY_WALKIE_HOST:
        display_target = DISPLAY_SHOW_WALKIE_MASTER_SETTING;
        break;
    case DISPLAY_WALKIE_RCVR:
        display_target = DISPLAY_SHOW_WALKIE_SLAVE_SETTING;
        break;
    case DISPLAY_SYSTEM_RESTART:
        display_target = DISPLAY_SHOW_SYSTEM_RESTART;
        break;
    default:
        break;
    }

}

void display_main_UI(void){
    
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_6x10_tr);

    display_datetime();
    // display_location();
    // display_elevation();
    u8g2_SetFont(&display, u8g2_font_6x12_tr);
    display_battery();

    // if (gpio_get_level(CAMERA_ON_PIN) == HIGH) {
    //     display_camera_icon();
    // }

    u8g2_SetFont(&display, u8g2_font_5x8_tr);
    is_bk3266_on == true? draw_bluetooth_on():draw_bluetooth_off();
    is_walkie_mute == false?draw_walkie_on(): draw_walkie_off();
    

    u8g2_SetFont(&display, u8g2_font_9x15_tr);
    draw_top_speed();

    u8g2_SendBuffer(&display);
}


// === UI Elements ===
void display_datetime() {
    const char *time = _get_RTC_time();
    const char *date = _get_RTC_date();
    u8g2_DrawStr(&display, 1, 8, time);
    u8g2_DrawStr(&display, 35, 8, date);
}

// void display_location(){
//     u8g2_DrawStr(&display, 1, 18, gps_latitude);
//     u8g2_DrawStr(&display, 1, 28, gps_longitude);
// }

// void display_elevation(){
//     char el[260];
//     if(gps_elevation_type == 1){
//         snprintf(el, sizeof(el), "%dM", gps_elevation);
//     }else{
//         snprintf(el, sizeof(el), "%dFT", gps_elevation);
//     }
//     u8g2_DrawStr(&display, 88, 28, el);
// }

void display_battery(){
    char soc_str[16];
    int soc = max17043_read_soc();
    snprintf(soc_str,sizeof(soc_str),"%d%%",soc);
    u8g2_DrawStr(&display, 100, 8, soc_str);
}


void draw_walkie_on(void){
    const char *walkie= "WALKIE: ON";
    u8g2_DrawStr(&display, 60, 30, walkie);
}

void draw_walkie_off(void){
    if(is_walkie_on){
        const char *walkie= "WALKIE: MUTE";
        u8g2_DrawStr(&display, 60, 30, walkie);
    }else{
        const char *walkie= "WALKIE: OFF";
        u8g2_DrawStr(&display, 60, 30, walkie);
    }
}

void draw_bluetooth_on(void){
    const char *bluetooth = "BLUETOOTH: ON";
    u8g2_DrawStr(&display, 60, 20, bluetooth);
}

void draw_bluetooth_off(void){
    const char *bluetooth = "BLUETOOTH: OFF";
    u8g2_DrawStr(&display, 60, 20, bluetooth);
}

void draw_top_speed(void){
    const char *top_speed[128];
    u8g2_SetFont(&display, u8g2_font_9x15_tr);
    is_setting_on?snprintf(top_speed,sizeof(top_speed),"SET:ON"):snprintf(top_speed,sizeof(top_speed),"%dMPH",top_speed_gps);
    is_setting_on?u8g2_DrawStr(&display, 1, 28, top_speed):u8g2_DrawStr(&display, 5, 28, top_speed);
}

//===== FULL VIEW ====
void display_off(void){

    display_target = DISPLAY_EN_OFF;
    display_button_target = DISPLAY_EN_OFF;
    vTaskDelay(pdMS_TO_TICKS(1000));
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_6x10_tr);
    u8g2_SendBuffer(&display);
    display_en = LOW;

}



void display_low_battery_warning(void){

}

void display_dns_setting(void){
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
    u8g2_DrawStr(&display, 1, 30, "SETTINGS");
    u8g2_SendBuffer(&display);
}

void display_show_bk3266_bluetooth(void){
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR14_tr);
    u8g2_DrawStr(&display, 1, 30, "BLUETOOTH");
    u8g2_SendBuffer(&display);
}

void display_walkie_MASTER_setting(void){
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR12_tr);
    u8g2_DrawStr(&display, 1, 30, "WALKIE-HOST");
    u8g2_SendBuffer(&display);
}

void display_walkie_SLAVE_setting(void){
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR12_tr);
    u8g2_DrawStr(&display, 1, 30, "WALKIE-RECV");
    u8g2_SendBuffer(&display);
}

void display_walkie_SYNC_setting(void){ //THIS IS THE LONGER WAY BUT IDC
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
    u8g2_DrawStr(&display, 25, 30, "SYNC");
    u8g2_SendBuffer(&display);
    vTaskDelay(pdMS_TO_TICKS(150));
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
    u8g2_DrawStr(&display, 25, 30, "SYNC.");
    u8g2_SendBuffer(&display);
    vTaskDelay(pdMS_TO_TICKS(150));
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
    u8g2_DrawStr(&display, 25, 30, "SYNC..");
    u8g2_SendBuffer(&display);
    vTaskDelay(pdMS_TO_TICKS(150));
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
    u8g2_DrawStr(&display, 25, 30, "SYNC...");
    u8g2_SendBuffer(&display);

}

void display_show_walkie_paired_setting(void){
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
    u8g2_DrawStr(&display, 20, 30, "PAIRED");
    u8g2_SendBuffer(&display);
}

void display_show_cancled(void){
    u8g2_ClearBuffer(&display);
    u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
    u8g2_DrawStr(&display, 1, 30, "CANCLED");
    u8g2_SendBuffer(&display);
}

//WALKIE-TALKIE
    void display_show_walkie_master_search_setting(void){
        char found[32];
        snprintf(found,sizeof(found),"FOUND: %d", new_peers);
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_timB10_tr);
        u8g2_DrawStr(&display, 30, 10, "SEARCH");
        u8g2_DrawStr(&display, 30, 25, found);
        u8g2_SendBuffer(&display);
        vTaskDelay(pdMS_TO_TICKS(150));
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_timB10_tr);
        u8g2_DrawStr(&display, 30, 10, "SEARCH.");
        u8g2_DrawStr(&display, 30, 25, found);
        u8g2_SendBuffer(&display);
        vTaskDelay(pdMS_TO_TICKS(150));
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_timB10_tr);
        u8g2_DrawStr(&display, 30, 10, "SEARCH..");
        u8g2_DrawStr(&display, 30, 25, found);
        u8g2_SendBuffer(&display);
        vTaskDelay(pdMS_TO_TICKS(150));
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_timB10_tr);
        u8g2_DrawStr(&display, 30, 10, "SEARCH...");
        u8g2_DrawStr(&display, 30, 25, found);
        u8g2_SendBuffer(&display);
    }

    void display_show_walkie_slave_search_setting(void){
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
        u8g2_DrawStr(&display, 8, 30, "EXPOSED");
        u8g2_SendBuffer(&display);
    }

    void display_show_walkie_mute_sequence(void){
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_7x14_tr);
        if(is_walkie_mute){
            u8g2_DrawStr(&display, 3, 20, "WALKIE MUTE: ON");
        }else{
            u8g2_DrawStr(&display, 1, 20, "WALKIE MUTE: OFF");
        }
        u8g2_SendBuffer(&display);
    }

    void display_show_walkie_delete_sequence(void){
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_9x15_tr);
        u8g2_DrawStr(&display, 8, 20, "LEAVE PARTY?");
        u8g2_SendBuffer(&display);
    }

    void display_show_walkie_enter_pairing_sequence(void){
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_9x15_tr);
        u8g2_DrawStr(&display, 3, 20, "ENTER PAIRING?");
        u8g2_SendBuffer(&display);
    }


//BLUETOOTH
    void display_show_bk3266_bluetooth_pwr_sequence(void){
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_7x14_tr);
        if(!is_bk3266_on){
            u8g2_DrawStr(&display, 15, 25, "BLUETOOTH: OFF");
        }else{
            u8g2_DrawStr(&display, 17, 25, "BLUETOOTH: ON");
        }
        u8g2_SendBuffer(&display);
   
    }


//SYSTEM
    void display_show_system_restart(void){
        u8g2_ClearBuffer(&display);
        u8g2_SetFont(&display, u8g2_font_ncenR18_tr);
        u8g2_DrawStr(&display, 8, 30, "RESTART");
        u8g2_SendBuffer(&display);
    }

