#include "core/M5StickCPlus2.h"

M5Stack::StickCPlus2 stick = M5Stack::StickCPlus2();

void setup() {
  Serial.begin(115200);
  stick.init();
}

void loop() {
  batteryTest();
}

void buzzerTest() {
  stick.updateButtons();
  if (stick.btnA.isPressed())
    stick.buzzer.tone(1000, 50);
  if (stick.btnB.isPressed())
    stick.buzzer.tone(2000, 50);
  if (stick.btnC.isPressed())
    stick.buzzer.tone(4000, 50);
}

void micTest() {
  stick.mic.update();
  for (int i = 0; i < stick.mic.samples_read; i++)
    Serial.println(stick.mic.raw_samples[i]);
}

void timeTest() {
  M5Stack::BM8563_Time time = stick.time.getTime();
  M5Stack::BM8563_Date date = stick.time.getDate();
  Serial.printf("seconds:%d;\tminutes:%d;\thours:%d;\t", time.seconds, time.minutes, time.hours);
  Serial.printf("weekDay:%d;\tdate:%d;\tmonth:%d;\tyear:%d;\n", date.weekDay, date.date, date.month, date.year);
  delay(1000);
}

void imuTest() {
  M5Stack::Point3 gyro = stick.imu.getGyro();
  M5Stack::Point3 accel = stick.imu.getAccel();
  float t = stick.imu.getTemp();
  Serial.printf("gx:%f;\tgy:%f;\tgz:%f;\tax:%f;\tay:%f;\taz:%f;\tt:%f;\n", gyro.x, gyro.y, gyro.z, accel.x, accel.y, accel.z, t);
  delay(100);
}

void displayTest() {
  stick.updateButtons();
  if (stick.btnA.isPressed())
    stick.lcd.fillScreen(BLACK);

  int x1 = random(stick.lcd.width());
  int y1 = random(stick.lcd.height());
  int x2 = random(stick.lcd.width());
  int y2 = random(stick.lcd.height());
  int color = random(WHITE);
  stick.lcd.drawLine(x1, y1, x2, y2, color);
  delay(100);
}

void batteryTest() {
  Serial.println(stick.battery.getVoltage());
  delay(100);
}