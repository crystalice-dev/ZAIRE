#include <globalVar.h>
#include <zaire_system.h>


bool is_esp_now_active;
int is_setting_on = false;
bool is_walkie_on = false;
bool is_walkie_mute = true;
uint8_t current_BT_vol = 11;
int top_speed_gps = 0;
user_settings_t user_settings;

esp_err_t zaire_system_init(){

    zaire_reset_all_pins();

    if(init_spiffs() != ZAIRE_OK)return ZAIRE_FAIL;
    if(init_uart() != ZAIRE_OK)return ZAIRE_FAIL;
    if(NVS_init() != ZAIRE_OK) return ZAIRE_FAIL;
    if(init_gpio() != ZAIRE_OK)return ZAIRE_FAIL;
    if(buzzer_init() != ZAIRE_OK)return ZAIRE_FAIL;
    // if(init_walkie() != ZAIRE_OK)return ZAIRE_FAIL;
    if(camera_init() != ZAIRE_OK)return ZAIRE_FAIL;// -- DO NOT FORGET TO COMMENT OUT u8g2's i2c before taking thi comment out
    if(usb_init() != ZAIRE_OK)return ZAIRE_FAIL;
    if(init_display() != ZAIRE_OK)return ZAIRE_FAIL;
//    // if(max17043_init() != ZAIRE_OK)return ZAIRE_FAIL;
    if(network_init() != ZAIRE_OK)return ZAIRE_FAIL;
//     if(init_bk3266() != ZAIRE_OK)return ZAIRE_FAIL;

    return ZAIRE_OK;
}

void zaire_reset_all_pins(){
    gpio_reset_pin(GPIO_NUM_0);
    gpio_reset_pin(GPIO_NUM_1);
    gpio_reset_pin(GPIO_NUM_2);
    gpio_reset_pin(GPIO_NUM_3);
    gpio_reset_pin(GPIO_NUM_4);
    gpio_reset_pin(GPIO_NUM_5);
    gpio_reset_pin(GPIO_NUM_6);
    gpio_reset_pin(GPIO_NUM_7);
    gpio_reset_pin(GPIO_NUM_8);
    gpio_reset_pin(GPIO_NUM_9);
    gpio_reset_pin(GPIO_NUM_10);
    gpio_reset_pin(GPIO_NUM_11);
    gpio_reset_pin(GPIO_NUM_12);
    gpio_reset_pin(GPIO_NUM_13);
    gpio_reset_pin(GPIO_NUM_14);
    gpio_reset_pin(GPIO_NUM_15);
    gpio_reset_pin(GPIO_NUM_16);
    gpio_reset_pin(GPIO_NUM_17);
    gpio_reset_pin(GPIO_NUM_18);
    gpio_reset_pin(GPIO_NUM_19);
    gpio_reset_pin(GPIO_NUM_20);
    gpio_reset_pin(GPIO_NUM_21);
    gpio_reset_pin(GPIO_NUM_38);
    gpio_reset_pin(GPIO_NUM_40);
    gpio_reset_pin(GPIO_NUM_41);
    gpio_reset_pin(GPIO_NUM_42);
    gpio_reset_pin(GPIO_NUM_45);
    gpio_reset_pin(GPIO_NUM_46);
    gpio_reset_pin(GPIO_NUM_47);
    gpio_reset_pin(GPIO_NUM_48);
    
}

esp_err_t init_spiffs(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "storage",   // <-- must match your partition CSV label
        .max_files = 8,
        .format_if_mount_failed = true  // set false in production once stable
    };

    if(esp_vfs_spiffs_register(&conf) != ZAIRE_OK)return ZAIRE_FAIL;
   

    size_t total = 0, used = 0;
    if(esp_spiffs_info(conf.partition_label, &total, &used) != ZAIRE_OK) return ZAIRE_FAIL;
    printf("total: %d used: %d\n", total, used);
  
    // Optional: list files for sanity
    DIR *d = opendir("/spiffs");
    if (d) {
        struct dirent *e;
        closedir(d);
    }

    return ZAIRE_OK;
}