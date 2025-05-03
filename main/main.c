/*
    TITLE: S2-HUB
    DESC: Serves web content in APSTA mode with captive portal DNS hijack
*/

#include <globalVar.h>
#include <esp_spiffs.h>

void init_spiffs(void) {
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "storage",
        .max_files = 5,
        .format_if_mount_failed = true
    };
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));

    size_t total = 0, used = 0;
    esp_err_t res = esp_spiffs_info(conf.partition_label, &total, &used);

    if(res == ESP_OK){
        ESP_LOGI("SPIFF", "Total: %d, Used: %d, Left: %d", total, used, total - used);
    }else{
        ESP_LOGI("SPIFF", "No");
    }
}

void i2c_scan(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_0_SDA,
        .scl_io_num = I2C_0_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    for (uint8_t addr = 1; addr < 127; addr++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        esp_err_t err = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);

        if (err == ESP_OK) {
            printf("Found device at 0x%02X\n", addr);
        }
    }
}


void app_main(void){

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    init_spiffs();

    //Global Inits
    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(display_init());
    ESP_ERROR_CHECK(init_i2s());
    ESP_ERROR_CHECK(init_usb_mic());

    
    ESP_LOGI("BOOT", "Device -- %s", DEVICE_NAME);

    

    start_dns_server();
    
}

