#pragma once

#include <WiFi.h>
#include "../MenuItem.h"

namespace Main {

class AccessPoint : public MenuItem {

private:
  String ssid = "test_access_point";
  String password = "test_password";

public:
  AccessPoint()
    : MenuItem("ACCESS POINT") {}

  void run() override {
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    stick->lcd.fillScreen(BLACK);
    stick->lcd.setTextSize(2);
    stick->lcd.printCenter(ssid, stick->lcd.width() / 2, stick->lcd.height() / 3);
    stick->lcd.printCenter(password, stick->lcd.width() / 2, stick->lcd.height() * 2 / 3);

    while (true) {
      tick();
      if (exitTrigger())
        return;
    }

    WiFi.softAPdisconnect(true);
  }
};

}
