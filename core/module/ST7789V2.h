#pragma once

#include "Adafruit_ST7789.h"

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

namespace M5Stack {

class ST7789V2 : public Adafruit_ST7789 {

public:
  ST7789V2(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst, int8_t bl)
    : Adafruit_ST7789(cs, dc, mosi, sclk, rst) {
    pinMode(bl, OUTPUT);
    digitalWrite(bl, HIGH);
  }
};

}