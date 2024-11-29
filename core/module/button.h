#pragma once

#define BTN_HOLD_TIME 2000

namespace M5Stack {

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
    return currentState == ButtonState::Released && previousState != ButtonState::Released;
  }

  bool isPressed() {
    return currentState == ButtonState::Pressed && previousState == ButtonState::Released;
  }

  bool isHolded() {
    return currentState == ButtonState::Holded && previousState == ButtonState::Pressed;
  }
};

}