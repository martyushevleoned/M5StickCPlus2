#pragma once

namespace Core {

class Battery {

private:
  const float minVoltage = 3.3;
  const float maxVoltage = 4.3;
  int pin;

public:
  Battery(const int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
  }

  float getVoltage() {
    return analogRead(pin) * 3.3 * 2.0 / 4095.0;
  }

  float getBatteryChargePercent() {
    return (getVoltage() - minVoltage) / (maxVoltage - minVoltage) * 100;
  }
};

}