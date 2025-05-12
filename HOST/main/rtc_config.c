#include <globalVar.h>



char* _get_RTC_time() { 
    static char time_str[20]; // ✅ Persists after function ends
    char minutes_str[6]; 
    char hours_str[6]; 
    uint8_t data[3];

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x00, true); // Start at register 0
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 3, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(WORKING_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    snprintf(minutes_str, sizeof(minutes_str), "%02d", bcd_to_dec(data[1]));
    snprintf(hours_str, sizeof(hours_str), "%02d", bcd_to_dec(data[2]));
    snprintf(time_str, sizeof(time_str), "%s:%s", hours_str, minutes_str);
    
    return time_str;
}

char* _get_RTC_date() {
    static char date_str[12]; // "MMM-DD" or "ERR-DD"
    uint8_t data[4];

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x03, true); // Start at day register (0x03 = day, date, month, year)
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 4, I2C_MASTER_LAST_NACK); // day, date, month, year
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(WORKING_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        snprintf(date_str, sizeof(date_str), "ERR");
        return date_str;
    }

    const char* months[] = {
        "ERR", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
        "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
    };

    uint8_t day = bcd_to_dec(data[1]);    // Date (01–31)
    uint8_t month = bcd_to_dec(data[2]);  // Month (01–12)

    const char* month_str = (month >= 1 && month <= 12) ? months[month] : "ERR";
    snprintf(date_str, sizeof(date_str), "%s-%02d", month_str, day);
    return date_str;
}



 //set_RTC(13, 44, 0, 1, 4, 5, 25); // Set to May 3, 2024 12:34:56 -- example
esp_err_t set_RTC(uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t date, char* _month, uint8_t year) {

    uint8_t month = _get_real_month(_month);

    uint8_t data[8];
    data[0] = 0x00; // Start at register 0
    data[1] = dec_to_bcd(sec);
    data[2] = dec_to_bcd(min);
    data[3] = dec_to_bcd(hour);
    data[4] = dec_to_bcd(day);   // 1=Sun, 2=Mon, etc.
    data[5] = dec_to_bcd(date);
    data[6] = dec_to_bcd(month);
    data[7] = dec_to_bcd(year);  // 24 for 2024



    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, data, 8, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(WORKING_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    if(ret != ESP_OK){
        printf("NO RTC\n");
        return ESP_FAIL;
    }

    return ESP_OK;
}


// === BCD helpers ===
uint8_t dec_to_bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

uint8_t bcd_to_dec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

// === GET REAL MONTH ===
uint8_t _get_real_month(const char* month) {
    const char* months[] = {
        "ERR", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    for (int i = 1; i <= 12; i++) {
        if (strcmp(month, months[i]) == 0) {
            return i;
        }
    }

    return 0; // return as error
}
