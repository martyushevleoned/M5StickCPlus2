#pragma once

#include "../MenuItem.h"

namespace Main {

class ST7789V2Test : public MenuItem {

public:
  ST7789V2Test()
    : MenuItem("ST7789V2") {
      setTickRate(1);
    }

  void run() override {

    int test = 0;
    int countOfTest = 4;

    while (true) {

      stick->lcd.fillScreen(BLACK);
      switch (test) {
        case 0:
          rgbToCmyk();
          break;
        case 1:
          circles();
          break;
        case 2:
          horizontalLines();
          break;
        case 3:
          verticalLines();
          break;
      }

      test++;
      test %= countOfTest;

      tick();
      if (exitTrigger())
        return;
    }
  }

private:
  void rgbToCmyk() {
    stick->lcd.fillRectHGradient(0, 0, stick->lcd.width(), stick->lcd.height() / 3, RED, CYAN);
    stick->lcd.fillRectHGradient(0, stick->lcd.height() / 3, stick->lcd.width(), stick->lcd.height() / 3, GREEN, MAGENTA);
    stick->lcd.fillRectHGradient(0, stick->lcd.height() * 2 / 3, stick->lcd.width(), stick->lcd.height() / 3, BLUE, YELLOW);
  }

  void circles() {
    for (int i = 0; i < 100; i++)
      stick->lcd.fillSmoothCircle(random(stick->lcd.width()), random(stick->lcd.height()), 5, random(WHITE), BLACK);
  }

  void horizontalLines() {
    for (int height = 0; height < stick->lcd.height(); height++)
      stick->lcd.drawFastHLine(0, height, stick->lcd.width(), random(WHITE));
  }

  void verticalLines() {
    for (int width = 0; width < stick->lcd.width(); width++)
      stick->lcd.drawFastVLine(width, 0, stick->lcd.height(), random(WHITE));
  }
};

}
