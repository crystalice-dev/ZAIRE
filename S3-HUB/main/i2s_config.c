#include <globalVar.h>


#ifdef WALKIE_INCLUDED


int32_t *samples_32bit;
int16_t *samples_16bit;
uint8_t *samples_8bit ;
int16_t *recive_16bit;
int16_t *output_16bit;
const i2s_port_t REC_I2S_PORT = I2S_NUM_0;
const i2s_port_t SPK_I2S_PORT = I2S_NUM_1;

//mic
const i2s_config_t rec_i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
      .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S| I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 2,
      .dma_buf_len = 256,
//      .use_apll = false,
//      .tx_desc_auto_clear = false,
//      .fixed_mclk = 0
      };
//speaker
const i2s_config_t spk_i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
      .communication_format =(i2s_comm_format_t)(I2S_COMM_FORMAT_I2S),
      .intr_alloc_flags = 0,
      .dma_buf_count = 2,
      .dma_buf_len = 256,
};
const i2s_pin_config_t rec_pin_config = {
      .bck_io_num = WALKIE_BCK,   // BCKL
      .ws_io_num = WALKIE_WS,    // LRCL
      .data_out_num = -1, // not used (only for speakers)
      .data_in_num = WALKIE_DIN  //
};
const i2s_pin_config_t spk_pin_config = {
      .bck_io_num = WALKIE_BCK,
      .ws_io_num = WALKIE_WS,
      .data_out_num = WALKIE_DOUT,
      .data_in_num = -1   //Not used
};  
void I2SInit()
{
  samples_32bit = (int32_t *)malloc(sizeof(int32_t) * 128);
  samples_16bit = (int16_t *)malloc(sizeof(int16_t) * 128);
  samples_8bit =  (uint8_t *)malloc(sizeof(uint8_t) * 128);
  recive_16bit =  (int16_t *)malloc(sizeof(int16_t) * 128);
  output_16bit =  (int16_t *)malloc(2*sizeof(int16_t) * 128);

  esp_err_t err;
  err = i2s_driver_install(REC_I2S_PORT, &rec_i2s_config, 0, NULL);
  ESP_ERROR_CHECK(err);
  err = i2s_set_pin(REC_I2S_PORT, &rec_pin_config);
  ESP_ERROR_CHECK(err);
  err = i2s_driver_install(SPK_I2S_PORT, &spk_i2s_config, 0, NULL);
  ESP_ERROR_CHECK(err);
  err = i2s_set_pin(SPK_I2S_PORT, &spk_pin_config);
  ESP_ERROR_CHECK(err);
  } 
int I2Sread(int16_t *samples, int count)// read from i2s
{
    size_t bytes_read = 0;
    if (count>128)
    {
        count = 128;//最少读取128
    }
    i2s_read(REC_I2S_PORT, (char *)samples_32bit, sizeof(int32_t) * count, &bytes_read, portMAX_DELAY);
    int samples_read = bytes_read / sizeof(int32_t);
    for (int i = 0; i < samples_read; i++)
    {
        int32_t temp = samples_32bit[i] >> 11;
        samples[i] = (temp > INT16_MAX) ? INT16_MAX : (temp < -INT16_MAX) ? -INT16_MAX : (int16_t)temp;
    }
    return samples_read;
}
void covert_bit(int16_t *temp_samples_16bit,uint8_t*temp_samples_8bit,uint8_t len )//16位数据转成8位
{
  for(uint8_t i=0;i<len;i++)
  {
    temp_samples_8bit[i]=(temp_samples_16bit[i] + 32768) >> 8;
  }
    
}
void I2Swrite(int16_t *samples, int count)//数据写入IIS
{
    size_t bytes_written;
    i2s_write(SPK_I2S_PORT, samples, sizeof(uint16_t)*count*2, &bytes_written, portMAX_DELAY); 
    printf("I2Swrite L: %d\n", bytes_written / sizeof(uint16_t) / 2);
}


#endif