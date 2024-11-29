#pragma once

#include "../MenuItem.h"

namespace Main {

class MPU6886Test : public MenuItem {

public:
  MPU6886Test()
    : MenuItem("MPU6886") {}

  void run() override {

    stick->lcd.fillScreen(BLACK);
    stick->lcd.setTextSize(2);

    int padding = 7;
    int height = 2 * stick->lcd.fontHeight();

    while (true) {

      Core::Point3 accel = stick->imu.getAccel();
      stick->lcd.setCursor(padding, padding);
      stick->lcd.print("ax=" + String(accel.x) + "  ");
      stick->lcd.setCursor(padding, padding + height);
      stick->lcd.print("ay=" + String(accel.y) + "  ");
      stick->lcd.setCursor(padding, padding + 2 * height);
      stick->lcd.print("az=" + String(accel.z) + "  ");

      Core::Point3 gyro = stick->imu.getGyro();
      stick->lcd.setCursor(stick->lcd.width() / 2 + padding, padding);
      stick->lcd.print("gx=" + String(gyro.x, 2) + "   ");
      stick->lcd.setCursor(stick->lcd.width() / 2 + padding, padding + height);
      stick->lcd.print("gy=" + String(gyro.y, 2) + "   ");
      stick->lcd.setCursor(stick->lcd.width() / 2 + padding, padding + 2 * height);
      stick->lcd.print("gz=" + String(gyro.z, 2) + "   ");

      float temp = stick->imu.getTemp();
      stick->lcd.setCursor(padding, padding + 3 * height);
      stick->lcd.print("temp=" + String(temp, 2) + "   ");

      tick();
      if (exitTrigger())
        return;
    }
  }
};

}
