#pragma once

namespace M5Stack {

class Battery {

private:
  int8_t pin;

public:
  Battery(int8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
  }

  float getVoltage() {
    return analogRead(pin) * 3.3 * 2.0 / 4095.0;
  }
};

}