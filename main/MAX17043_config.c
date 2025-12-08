#include <globalVar.h>


#define TAG "MAX17043"
#define I2C_PORT      I2C_NUM_1
#define I2C_ADDR      0x36   // 7-bit
#define REG_VCELL     0x02
#define REG_SOC       0x04
#define REG_MODE      0x06
#define REG_VERSION   0x08
#define REG_CONFIG    0x0C   // 0x0C MSB, 0x0D LSB
#define REG_COMMAND   0xFE

static esp_err_t max17043_read_u16(uint8_t reg, uint16_t *out)
{
    uint8_t buf[2];
    esp_err_t err = i2c_master_write_read_device(I2C_PORT, I2C_ADDR, &reg, 1, buf, 2, 1000/portTICK_PERIOD_MS);
    if (err == ESP_OK) *out = ((uint16_t)buf[0] << 8) | buf[1];
    return err;
}

static esp_err_t max17043_write_u16(uint8_t reg, uint16_t val)
{
    uint8_t buf[3] = { reg, (uint8_t)(val >> 8), (uint8_t)(val & 0xFF) };
    return i2c_master_write_to_device(I2C_PORT, I2C_ADDR, buf, sizeof(buf), 1000/portTICK_PERIOD_MS);
}


esp_err_t max17043_init(void)
{
    // Write 0x4000 to MODE to re-start fuel-gauge algorithm
    return max17043_write_u16(REG_MODE, 0x4000);
}

static esp_err_t max17043_set_alert_percent(uint8_t percent_1_to_32)
{
    if (percent_1_to_32 < 1 || percent_1_to_32 > 32) return ESP_ERR_INVALID_ARG;
    // Encode: 1%->0x1F, ..., 32%->0x00  (two's-complement mapping in datasheet)
    uint8_t athd_code = (uint8_t)((32 - percent_1_to_32) & 0x1F);

    uint16_t cfg = 0;
    ESP_ERROR_CHECK(max17043_read_u16(REG_CONFIG, &cfg));
    uint8_t msb = (cfg >> 8) & 0xFF;    // RCOMP etc. (leave unchanged)
    uint8_t lsb = cfg & 0xFF;           // [7]=SLEEP, [6]=X, [5]=ALRT, [4:0]=ATHD

    lsb = (lsb & 0xE0) | athd_code;     // keep SLEEP/X/ALRT, set ATHD
    return max17043_write_u16(REG_CONFIG, ((uint16_t)msb << 8) | lsb);
}

float max17043_read_voltage(void)
{
    uint16_t raw = 0;
    if (max17043_read_u16(REG_VCELL, &raw) != ESP_OK) return -1.0f;
    raw >>= 4;                       // 12-bit value
    return (float)raw * 1.25f / 1000.0f; // volts (1.25 mV/LSB)
}

float max17043_read_soc(void)
{
    max17043_init();
    vTaskDelay(pdMS_TO_TICKS(500));
    uint16_t raw = 0;
    if (max17043_read_u16(REG_SOC, &raw) != ESP_OK) return -1.0f;
    uint8_t intp = (raw >> 8) & 0xFF;
    uint8_t frac = raw & 0xFF;
    return (float)intp + ((float)frac / 256.0f);
}