#include <globalVar.h>


// --- TIME: HH:MM (handles 12/24h) ---
char* _get_RTC_time(void){
    static char time_str[9]; // "HH:MM"
    uint8_t d[3];

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR<<1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x00, true); // seconds
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR<<1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, d, 3, I2C_MASTER_LAST_NACK); // sec,min,hour
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(ACC_I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK){ snprintf(time_str, sizeof(time_str), "ERR"); return time_str; }

    uint8_t sec = bcd_to_dec(d[0] & 0x7F); (void)sec; // not used
    uint8_t min = bcd_to_dec(d[1] & 0x7F);
    uint8_t hrb = d[2];
    uint8_t hour;
    if (hrb & 0x40){ // 12h mode
        hour = bcd_to_dec(hrb & 0x1F);
        bool pm = hrb & 0x20;
        if (hour == 12) hour = 0;
        hour += pm ? 12 : 0;
    } else {
        hour = bcd_to_dec(hrb & 0x3F); // 24h
    }
    snprintf(time_str, sizeof(time_str), "%02u:%02u", hour, min);
    return time_str;
}

// --- DATE: "MMM-DD-YYYY" ---
char* _get_RTC_date(void){
    static char date_str[16];
    uint8_t d[4];

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR<<1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x03, true); // day, date, month, year
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR<<1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, d, 4, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(ACC_I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK){ snprintf(date_str, sizeof(date_str), "ERR"); return date_str; }

    // d[0]=weekday (1..7, not BCD), d[1]=date(BCD), d[2]=month(BCD + century bit7), d[3]=year(BCD)
    static const char* months[] = {"ERR","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
    uint8_t day    = bcd_to_dec(d[1] & 0x3F);
    uint8_t mon_b  = d[2];
    uint8_t month  = bcd_to_dec(mon_b & 0x1F);
    uint8_t y2     = bcd_to_dec(d[3]);
    int full_year  = ((mon_b & 0x80) ? 2100 : 2000) + y2; // century bit

    const char* m  = (month>=1 && month<=12) ? months[month] : "ERR";
    snprintf(date_str, sizeof(date_str), "%s-%02u", m, day);
    return date_str;
}

// set_RTC(19,40,10,4,1,"Sep",25); // 2025-09-01 Mon 19:40:10
esp_err_t set_RTC(uint8_t hour, uint8_t min, uint8_t sec, uint8_t weekday, uint8_t date, char* _month, uint8_t year){
#ifdef DISPLAY_INCLUDED
    gpio_set_level(DISPLAY_EN_PIN, HIGH);
#endif
    vTaskDelay(pdMS_TO_TICKS(10)); // 3s is overkill

    uint8_t month = _get_real_month(_month);

    // --- write 0x00..0x03: sec,min,hour,weekday
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR<<1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x00, true);
    uint8_t b1[] = {
        dec_to_bcd(sec) & 0x7F,    // CH=0 (DS1307), fine on DS3231
        dec_to_bcd(min) & 0x7F,
        dec_to_bcd(hour) & 0x3F,   // force 24h
        dec_to_bcd(weekday) & 0x07 // 1..7
    };
    i2c_master_write(cmd, b1, sizeof(b1), true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) goto done;

    // --- write 0x04..0x06: date, month, year
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR<<1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x04, true);
    uint8_t b2[] = {
        dec_to_bcd(date)  & 0x3F,
        dec_to_bcd(month) & 0x1F,  // leave century=0
        dec_to_bcd(year)           // 0..99 (e.g., 25 for 2025)
    };
    i2c_master_write(cmd, b2, sizeof(b2), true);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

done:
#ifdef DISPLAY_INCLUDED
    gpio_set_level(DISPLAY_EN_PIN, LOW);
#endif
    return ret;
}

// "Jan".."Dec" → 1..12
uint8_t _get_real_month(const char* month){
    static const char* months[] = {"ERR","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i=1;i<=12;i++) if (strcmp(month, months[i])==0) return i;
    return 0;
}

// === BCD helpers ===
uint8_t dec_to_bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

uint8_t bcd_to_dec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

void test_time(void){
    
    printf("%s %s\n", _get_RTC_date(), _get_RTC_time()); // e.g., "SEP-01-2025 19:40"
}
