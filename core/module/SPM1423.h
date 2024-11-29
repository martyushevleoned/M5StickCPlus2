#pragma once

#include <driver/i2s.h>

#define SAMPLE_BUFFER_SIZE 512
#define SAMPLE_RATE 48000

namespace M5Stack {

class SPM1423 {

public:
  int32_t raw_samples[SAMPLE_BUFFER_SIZE];
  int samples_read;

  SPM1423(int i2s_clk, int i2s_data) {

    i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 2,
      .dma_buf_len = SAMPLE_BUFFER_SIZE,
    };
    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);

    i2s_pin_config_t i2s_mic_pins = {
      .bck_io_num = I2S_PIN_NO_CHANGE,
      .ws_io_num = i2s_clk,
      .data_out_num = I2S_PIN_NO_CHANGE,
      .data_in_num = i2s_data
    };
    i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);
  }

  void update() {
    size_t bytes_read = 0;
    i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * SAMPLE_BUFFER_SIZE, &bytes_read, portMAX_DELAY);
    samples_read = bytes_read / sizeof(int32_t);
  }
};

}