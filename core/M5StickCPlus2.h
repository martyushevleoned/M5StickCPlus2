#pragma once

#include "module/ST7789V2.h"
#include "module/BM8563.h"
#include "module/MPU6886.h"
#include "module/SPM1423.h"
#include "module/Battery.h"
#include "module/Buzzer.h"
#include "module/Button.h"
#include "module/Led.h"

#define POWER_HOLD_PIN 4

#define LED_PIN 19
#define BUZZ_PIN 2
#define BTN_A_PIN 37
#define BTN_B_PIN 39
#define BTN_C_PIN 35
#define BATTERY_PIN 38

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

#define I2S_CLOCK_PIN 0
#define I2S_DATA_PIN 34

#define LCD_CS 5
#define LCD_DC 14
#define LCD_MOSI 15
#define LCD_SCLK 13
#define LCD_RST 12
#define LCD_BL 27
#define LCD_WIDTH 135
#define LCD_HEIGHT 240
#define LCD_ROTATION 3

namespace Core {

class StickCPlus2 {

private:
  StickCPlus2() {}
  ~StickCPlus2() {}
  StickCPlus2(const StickCPlus2&);
  StickCPlus2& operator = (const StickCPlus2&);

public:
  static StickCPlus2* getInstance() {
    static StickCPlus2 instance;
    return &instance;
  }

  ST7789V2 lcd = ST7789V2();
  BM8563 time = BM8563(I2C_SDA_PIN, I2C_SCL_PIN, I2C_BM8563_DEFAULT_ADDRESS);
  MPU6886 imu = MPU6886(I2C_SDA_PIN, I2C_SCL_PIN, I2C_MPU6886_DEFAULT_ADDRESS);
  SPM1423 mic = SPM1423(I2S_CLOCK_PIN, I2S_DATA_PIN);
  Battery battery = Battery(BATTERY_PIN);
  Buzzer buzzer = Buzzer(BUZZ_PIN);
  Button btnA = Button(BTN_A_PIN);
  Button btnB = Button(BTN_B_PIN);
  Button btnC = Button(BTN_C_PIN);
  Led led = Led(LED_PIN);

  void init() {
    pinMode(POWER_HOLD_PIN, OUTPUT);
    digitalWrite(POWER_HOLD_PIN, HIGH);

    lcd.init();
    lcd.setRotation(LCD_ROTATION);
    lcd.fillScreen(BLACK);
    lcd.setTextWrap(false, false);

    time.init();
    time.setTime(30, 59, 23);
    time.setDate(6, 31, 12, 2024);

    imu.init();
  }

  void updateButtons() {
    btnA.update();
    btnB.update();
    btnC.update();
  }

  void powerOff() {
    digitalWrite(POWER_HOLD_PIN, LOW);
  }
};

}