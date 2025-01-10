#pragma once

#include "../MenuItem.h"

namespace Main {

class BuzzerTest : public MenuItem {

public:
  BuzzerTest()
    : MenuItem("BUZZER") {}

  void run() override {

    while (true) {
      stick->updateButtons();

      if(stick->btnA.isPressed())
        stick->buzzer.tone(1000, 50);

      if(stick->btnB.isPressed())
        stick->buzzer.tone(2000, 50);

      if(stick->btnC.isPressed())
        stick->buzzer.tone(4000, 50);

      tick();
      if (exitTrigger())
        return;
    }
  }
};

}
