#pragma once

#include <TFT_eSPI.h>

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

namespace Core {

class ST7789V2 : public TFT_eSPI {

public:
  ST7789V2(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst, int8_t bl)
    : TFT_eSPI() {
  }

  void printCenter(int32_t x, int32_t y, String text) {
    setCursor(x - textWidth(text) / 2, y - fontHeight() / 2);
    print(text);
  }

  void printCenter(String text) {
    printCenter(width() / 2, height() / 2, text);
  }

  void printRight(int32_t x, int32_t y, String text) {
    setCursor(x - textWidth(text), y);
    print(text);
  }

  void setWidthScaledTextSize(int32_t width, String text) {
    int lenght = text.length();
    if (lenght < 5) {
      setTextSize(8);
    } else if (lenght < 7) {
      setTextSize(6);
    } else if (lenght < 10) {
      setTextSize(4);
    } else {
      setTextSize(2);
    }
  }

  void setWidthScaledTextSize(String text) {
    setWidthScaledTextSize(width(), text);
  }
};

}