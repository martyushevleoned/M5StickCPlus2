#pragma once

namespace Core {

class Led {

private:
  int pin;

public:
  Led(const int pin) {
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