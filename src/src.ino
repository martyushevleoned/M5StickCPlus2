#include <M5StickCPlus2.h>

void setup() {
  StickCP2.begin(M5.config());
  StickCP2.Display.setRotation(1);
  StickCP2.Display.setTextColor(GREEN);
  StickCP2.Display.setTextDatum(middle_center);
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  StickCP2.Display.setTextSize(1);

  Serial.begin(9600);
  Serial.println("Press Btn to sleep");
  Serial.println("After 5s Wakeup");

  StickCP2.Display.drawString("BtnA Sleep 5s", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
}

void loop() {

    StickCP2.update();

    if (StickCP2.BtnA.wasPressed()) {
      Serial.println("Button A pressed");
    }

    if (StickCP2.BtnB.wasPressed()) {
      Serial.println("Button B pressed");
    }

    if (StickCP2.BtnA.isHolding() && StickCP2.BtnB.isHolding()) {
      Serial.println("Shutdown");
      StickCP2.Power.powerOff();
    }
}
