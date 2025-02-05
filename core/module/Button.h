#pragma once

#define BTN_HOLD_TIME 3000

namespace Core {

enum class ButtonState { Released,
                         Pressed,
                         Holded };

class Button {

private:
  int8_t pin;
  ButtonState previousState = ButtonState::Released;
  ButtonState currentState = ButtonState::Released;
  unsigned long lastReleaseTime = millis();

public:
  Button(int8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
  }

  void update() {

    previousState = currentState;
    if (digitalRead(pin) == HIGH) {

      currentState = ButtonState::Released;
      lastReleaseTime = millis();

    } else {
      if (millis() - lastReleaseTime < BTN_HOLD_TIME) {
        currentState = ButtonState::Pressed;
      } else {
        currentState = ButtonState::Holded;
      }
    }

  }

  bool isReleased() {
    return currentState == ButtonState::Released && (previousState == ButtonState::Pressed || previousState == ButtonState::Holded);
  }

  bool isPressed() {
    return currentState == ButtonState::Released && previousState == ButtonState::Pressed;
  }

  bool isHolded() {
    return currentState == ButtonState::Holded && previousState == ButtonState::Pressed;
  }
};

}