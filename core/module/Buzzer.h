#pragma once

namespace Core {

class Buzzer {

private:
  int8_t pin;

  void toneMicros(uint16_t frequency, unsigned long durationMicros, uint16_t q) {

    unsigned long period = 1000000 / frequency;
    unsigned long activePeriod = period / q;
    unsigned long startTime = micros();

    for (unsigned long currentDuration = 0; currentDuration < durationMicros; currentDuration = micros() - startTime) {

      if (currentDuration % period < activePeriod)
        digitalWrite(pin, HIGH);
      else
        digitalWrite(pin, LOW);
    }

  }

public:
  Buzzer(int8_t pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
  }

  void tone(uint16_t frequency, unsigned long durationMillis) {
    toneMicros(frequency, durationMillis * 1000, 2);
  }
};

}