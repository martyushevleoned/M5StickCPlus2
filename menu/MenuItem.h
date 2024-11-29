#pragma once

#include "../core/M5StickCPlus2.h"

#define PREVIEW_DURATION 700
#define DEFAULT_TICK_RATE 10

namespace Main {
  
class MenuItem {

private:
  String itemName;
  unsigned long lastTick = millis(); 
  unsigned long tickPeriod = 1000 / DEFAULT_TICK_RATE;  

protected:
  Core::StickCPlus2* stick = Core::StickCPlus2::getInstance();

  void setTickRate(float tickPerSecond) {
    tickPeriod = 1000 / tickPerSecond;
  }

  void tick() {
    if (millis() - lastTick < tickPeriod)
      delay(tickPeriod - (millis() - lastTick));
    lastTick = millis();
  }

public:
  MenuItem(String itemName) {
    this->itemName = itemName;
  }

  String name() {
    return itemName;
  }

  void preview() {
    stick->lcd.fillScreen(BLACK);
    stick->lcd.setWidthScaledTextSize(itemName);
    stick->lcd.printCenter(itemName);
    delay(PREVIEW_DURATION);
  }

  bool isExit() {
    return stick->btnB.isHolded();
  } 

  bool exitTrigger() {
    stick->btnB.update();
    return stick->btnB.isHolded();
  } 
  
  virtual void run() {
    Serial.printf("%s run\n", itemName);
  }
};

}
