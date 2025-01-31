#include "globalVar.h"



int init_i2c(){

    // I2C0 configuration
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_DATA,
        .scl_io_num = I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
    esp_err_t i2c_err0 = i2c_param_config(I2C_NUM_0, &i2c_config);
    esp_err_t i2c_err1 = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    if(i2c_err0 || i2c_err1){
        return ESP_FAIL;
    }

    return ESP_OK;
    
}