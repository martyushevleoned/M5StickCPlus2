#pragma once

#include "MenuItem.h"
#include <vector>
#include <memory>

namespace Main {

class Menu : public MenuItem {

private:
  int currentItem = 0;


  void display() {

    stick->lcd.fillScreen(backgroundColor);
    stick->lcd.setTextColor(textColor, backgroundColor);

    int padding = 3;
    stick->lcd.setTextSize(2);
    stick->lcd.setCursor(padding, padding);
    stick->lcd.print(name());
    stick->lcd.printRight(stick->lcd.width() - padding, padding, String(stick->battery.getVoltage()));

    int headerHeight = stick->lcd.fontHeight() + 2 * padding;
    stick->lcd.drawFastHLine(0, headerHeight, stick->lcd.width(), textColor);
    stick->lcd.setWidthScaledTextSize(items.at(currentItem)->name());
    stick->lcd.printCenter(stick->lcd.width() / 2, stick->lcd.height() / 2 + headerHeight, items.at(currentItem)->name());
  }

protected:
  std::vector<std::shared_ptr<MenuItem>> items;
  uint16_t backgroundColor;
  uint16_t textColor;

public:
  Menu(String menuName, std::vector<std::shared_ptr<MenuItem>> items, uint16_t textColor = WHITE, uint16_t backgroundColor = BLACK)
    : MenuItem(menuName) {
    this->items = items;
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;
  }

  void run() override {
    display();
    while (true) {
      tick();
      stick->updateButtons();

      if (stick->btnA.isPressed()) {
        items.at(currentItem)->preview();
        items.at(currentItem)->run();
        display();

      } else if (stick->btnB.isPressed()) {
        currentItem++;
        currentItem %= items.size();
        display();

      } else if (stick->btnC.isPressed()) {
        currentItem += items.size() - 1;
        currentItem %= items.size();
        display();

      } else if (stick->btnB.isHolded()) {
        return;

      } else if (stick->btnC.isHolded()) {
        stick->powerOff();
      }
    }
  }
};

}
