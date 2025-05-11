#include <globalVar.h>



float BATTERY_STATUS = 0;
float BATTERY_VOLTAGE;
uint8_t TEMP_STATUS = 0;



//INIT
esp_err_t i2c_init(void){
    esp_err_t ret_0, ret_1;
    //I2C_NUM_0
    i2c_config_t i2c_0_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_0_SDA,
        .scl_io_num = I2C_0_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    
    ret_0 = i2c_param_config(PARSE_I2C_NUM, &i2c_0_conf);
    ret_1 = i2c_driver_install(PARSE_I2C_NUM, I2C_MODE_MASTER, 0, 0, 0);

    #ifndef DISPLAY_INCLUDED //only if display is not included -- help RTC
        i2c_config_t i2c_1_conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = I2C_1_SDA,
            .scl_io_num = I2C_1_SCL,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = 100000
        };
        
        ESP_ERROR_CHECK(i2c_param_config(WORKING_I2C_NUM, &i2c_1_conf));
        ESP_ERROR_CHECK(i2c_driver_install(WORKING_I2C_NUM, I2C_MODE_MASTER, 0, 0, 0));
    #endif

    if(ret_0 != ESP_OK || ret_1 != ESP_OK){
        vTaskDelay(pdMS_TO_TICKS(2000));
        return ESP_FAIL;
    }

    return ESP_OK;
}


//===================== BATTERY===============
#define TAG            "battery"

esp_err_t battery_read16(uint8_t reg, uint16_t *out_val) {
    uint8_t data[2];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MAX17043_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MAX17043_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 2, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(PARSE_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE("BATTERY", "I2C read failed at reg 0x%02X: %s", reg, esp_err_to_name(ret));
    }

    if (ret == ESP_OK) {
        *out_val = (data[0] << 8) | data[1];
    }

    return ret;
}

esp_err_t battery_quick_start() {
    uint8_t data[2] = { 0x40, 0x00 }; // Set QuickStart bit

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MAX17043_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x06, true); // MODE register
    i2c_master_write(cmd, data, 2, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(PARSE_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t battery_init() {
    ESP_LOGI(TAG, "Initializing battery...");
    
    //battery_quick_start();
    vTaskDelay(pdMS_TO_TICKS(200));
    // // Optional: test read
    // uint16_t raw;
    // esp_err_t ret = battery_read16(0x02, &raw); // VCELL

    // if (ret != ESP_OK) {
    //     ESP_LOGE(TAG, "Failed to communicate with battery");
    //     return ret;
    // }

    // ESP_LOGI(TAG, "battery detected. VCELL raw: 0x%04X", raw);
    return ESP_OK;
}

float battery_get_voltage() {
    uint16_t raw;
    if (battery_read16(0x02, &raw) != ESP_OK) return -1.0;
    return (raw >> 4) * 1.25f / 1000.0f;
}

float battery_get_soc() {
    uint16_t raw;
    if (battery_read16(0x04, &raw) != ESP_OK) return -1.0;

    int soc = raw >> 8;  // Most significant byte = % SoC

    if (soc > 100) soc = 100;
    if (soc < 0) soc = 0;

    return (float)soc;
}


//LIGHTS
float lux = 0;
esp_err_t bh1750_init() {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BH1750_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x10, true); // Continuously H-Resolution Mode
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(PARSE_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    
    if(ret == ESP_FAIL){
        
        vTaskDelay(pdMS_TO_TICKS(5000));
    }

    return ret;
}

float bh1750_read_lux() {
    uint8_t data[2];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BH1750_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 2, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(PARSE_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) return -1.0;

    uint16_t raw = (data[0] << 8) | data[1];
    return raw / 1.2; // Convert to lux
}
