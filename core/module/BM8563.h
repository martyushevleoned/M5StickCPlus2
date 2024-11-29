#pragma once

#include <Wire.h>

#define I2C_BM8563_DEFAULT_ADDRESS 0x51

namespace Core {

struct BM8563_Time {
  int8_t hours;
  int8_t minutes;
  int8_t seconds;

  String toString() {
    String result;
    result += seconds < 10 ? "0" + String(seconds) : String(seconds);
    result += minutes < 10 ? ":0" + String(minutes) : ":" + String(minutes);
    result += hours < 10 ? ":0" + String(hours) : ":" + String(hours);
    return result;
  }
};

struct BM8563_Date {
  int8_t weekDay;
  int8_t date;
  int8_t month;
  int16_t year;

  String toString() {
    String result;
    result += date < 10 ? "0" + String(date) : String(date);
    result += month < 10 ? ".0" + String(month) : "." + String(month);
    result += "." + String(year % 100);
    return result;
  }
};

class BM8563 {

private:
  int deviceAddress;
  TwoWire* wire;
  BM8563_Time time;
  BM8563_Date date;

  uint8_t bcd2ToByte(uint8_t value) {
    uint8_t tmp = ((uint8_t)(value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (value & (uint8_t)0x0F));
  }

  uint8_t byteToBcd2(uint8_t value) {
    return ((uint8_t)((value / 10) << 4) | (value %= 10));
  }

  void writeReg(uint8_t reg, uint8_t data) {
    wire->beginTransmission(deviceAddress);
    wire->write(reg);
    wire->write(data);
    wire->endTransmission();
  }

  uint8_t readReg(uint8_t reg) {
    wire->beginTransmission(deviceAddress);
    wire->write(reg);
    wire->endTransmission(false);
    wire->requestFrom(deviceAddress, 1);
    return wire->read();
  }

public:
  BM8563(int i2c_sda, int i2c_clk, int deviceAddress) {
    Wire1.begin(i2c_sda, i2c_clk);
    this->wire = &Wire1;
    this->deviceAddress = deviceAddress;
  }

  void init() {
    wire->beginTransmission(deviceAddress);
    wire->write(0x00);
    wire->write(0x00);
    wire->write(0x00);
    wire->endTransmission();
  }

  BM8563_Time getTime() {
    wire->beginTransmission(deviceAddress);
    wire->write(0x02);
    wire->endTransmission(false);
    wire->requestFrom(deviceAddress, 3);

    uint8_t buf[3];
    while (wire->available()) {
      buf[0] = wire->read();
      buf[1] = wire->read();
      buf[2] = wire->read();
    }

    time.seconds = bcd2ToByte(buf[0] & 0x7f);
    time.minutes = bcd2ToByte(buf[1] & 0x7f);
    time.hours = bcd2ToByte(buf[2] & 0x3f);

    return time;
  }

  void setTime(int8_t seconds, int8_t minutes, int8_t hours) {
    wire->beginTransmission(deviceAddress);
    wire->write(0x02);
    wire->write(byteToBcd2(seconds));
    wire->write(byteToBcd2(minutes));
    wire->write(byteToBcd2(hours));
    wire->endTransmission();
  }

  BM8563_Date getDate() {
    wire->beginTransmission(deviceAddress);
    wire->write(0x05);
    wire->endTransmission(false);
    wire->requestFrom(deviceAddress, 4);

    uint8_t buf[4];
    while (wire->available()) {
      buf[0] = wire->read();
      buf[1] = wire->read();
      buf[2] = wire->read();
      buf[3] = wire->read();
    }

    date.date = bcd2ToByte(buf[0] & 0x3f);
    date.weekDay = bcd2ToByte(buf[1] & 0x07);
    date.month = bcd2ToByte(buf[2] & 0x1f);

    if (buf[2] & 0x80)
      date.year = 1900 + bcd2ToByte(buf[3] & 0xff);
    else
      date.year = 2000 + bcd2ToByte(buf[3] & 0xff);

    return date;
  }

  void setDate(int8_t weekDay, int8_t date, int8_t month, int16_t year) {
    wire->beginTransmission(deviceAddress);
    wire->write(0x05);
    wire->write(byteToBcd2(date));
    wire->write(byteToBcd2(weekDay));

    if (year < 2000)
      wire->write(byteToBcd2(month) | 0x80);
    else
      wire->write(byteToBcd2(month) | 0x00);

    wire->write(byteToBcd2((uint8_t)(year % 100)));
    wire->endTransmission();
  }
};

}
