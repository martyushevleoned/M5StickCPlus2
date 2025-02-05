#pragma once

#include "menu/Menu.h"
#include "menu/test/BuzzerTest.h"
#include "menu/test/BM8563Test.h"
#include "menu/test/ST7789V2Test.h"
#include "menu/test/MPU6886Test.h"
#include "menu/app/Spectroid.h"
#include "menu/wifi/AccessPoint.h"

Main::Menu menu = Main::Menu("Main", { 
  std::make_shared<Main::Menu>(Main::Menu("Test", { 
    std::make_shared<Main::BuzzerTest>(Main::BuzzerTest()),
    std::make_shared<Main::BM8563Test>(Main::BM8563Test()), 
    std::make_shared<Main::ST7789V2Test>(Main::ST7789V2Test()), 
    std::make_shared<Main::MPU6886Test>(Main::MPU6886Test())
    }, GREEN)), 
  std::make_shared<Main::Menu>(Main::Menu("App", { 
    std::make_shared<Main::Spectroid>(Main::Spectroid()) 
    }, BLUE)), 
  std::make_shared<Main::Menu>(Main::Menu("WiFi", { 
    std::make_shared<Main::AccessPoint>(Main::AccessPoint())
    }, RED)) 
  }, MAGENTA);

void setup() {
  Serial.begin(115200);
  Core::StickCPlus2::getInstance()->init();
}

void loop() {
  menu.run();
}
