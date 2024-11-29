#pragma once

#include "../MenuItem.h"

namespace Main {

class BM8563Test : public MenuItem {

public:
  BM8563Test()
    : MenuItem("BM8563") {
      setTickRate(1);
    }

  void run() override {

    stick->lcd.fillScreen(BLACK);
    stick->lcd.setWidthScaledTextSize("00:00:00");

    while (true) {
      
      stick->lcd.printCenter(stick->lcd.width() / 2, stick->lcd.height() / 3, stick->time.getTime().toString());
      stick->lcd.printCenter(stick->lcd.width() / 2, stick->lcd.height() * 2 / 3, stick->time.getDate().toString());

      tick();
      if (exitTrigger())
        return;
    }
  }
};

}
