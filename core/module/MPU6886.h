#pragma once

#include <Wire.h>

#define I2C_MPU6886_DEFAULT_ADDRESS 0x68

namespace M5Stack {

struct Point3 {
  float x;
  float y;
  float z;
};

class MPU6886 {

private:
  int deviceAddress;
  TwoWire *wire;
  Point3 point;
  float aRes = 8.0 / 32768.0;
  float gRes = 2000.0 / 32768.0;

  void writeByte(uint8_t address, uint8_t data) {
    delay(5);
    wire->beginTransmission(deviceAddress);
    wire->write(address);
    wire->write(data);
    wire->endTransmission();
  }

  uint8_t readByte(uint8_t address) {
    wire->beginTransmission(deviceAddress);
    wire->write(address);
    wire->endTransmission();
    wire->requestFrom(deviceAddress, 1);
    return wire->read();;
  }

public:
  MPU6886(int i2c_sda, int i2c_clk, int deviceAddress) {
    Wire1.begin(i2c_sda, i2c_clk);
    this->wire = &Wire1;
    this->deviceAddress = deviceAddress;
  }

  void init(void) {
    writeByte(0x6b, 0x00);
    writeByte(0x6b, 1 << 7);
    writeByte(0x6b, 1 << 0);
    writeByte(0x1c, 0x10);
    writeByte(0x1b, 0x18);
    writeByte(0x1a, 0x01);
    writeByte(0x19, 0x05);
    writeByte(0x38, 0x00);
    writeByte(0x1d, 0x00);
    writeByte(0x6a, 0x00);
    writeByte(0x23, 0x00);
    writeByte(0x37, 0x22);
    writeByte(0x38, 0x01);
  }

  Point3 getAccel() {
    point.x = (int16_t)((readByte(0x3b) << 8) | readByte(0x3c)) * aRes;
    point.y = (int16_t)((readByte(0x3d) << 8) | readByte(0x3e)) * aRes;
    point.z = (int16_t)((readByte(0x3f) << 8) | readByte(0x40)) * aRes;
    return point;
  }

  Point3 getGyro() {
    point.x = (int16_t)((readByte(0x43) << 8) | readByte(0x44)) * gRes;
    point.y = (int16_t)((readByte(0x45) << 8) | readByte(0x46)) * gRes;
    point.z = (int16_t)((readByte(0x47) << 8) | readByte(0x48)) * gRes;
    return point;
  }

  float getTemp() {
    return 25.0 + ((readByte(0x41) << 8) | readByte(0x42)) / 326.8;;
  }
};

}