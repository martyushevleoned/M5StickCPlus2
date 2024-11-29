#pragma once

namespace Core {

class Led {

private:
  int8_t pin;

public:
  Led(int8_t pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
  }

  void turnOn() {
    digitalWrite(pin, HIGH);
  }

  void turnOff() {
    digitalWrite(pin, LOW);
  }
};

}