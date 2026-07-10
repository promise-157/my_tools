#include "i2c.h"
#include "../delay/delay.h"

I2C::I2C() : I2C_SCL(true), I2C_SDA(true) {}
void I2C::start() {
  setSDA(true);
  delay_us(1);
  setSCL(true);
  setSDA(false);
  delay_us(1);
  setSCL(false);
}
void I2C::stop() {
  setSDA(false);
  delay_us(1);
  setSCL(true);
  setSDA(true);
  delay_us(1);
}
void I2C::writeByte(uint8_t byte) {
  for (int i = 0; i < 8; i++) {
    setSDA((byte & 0x80) != 0);
    delay_us(1);
    setSCL(true);
    delay_us(1);
    setSCL(false);
    byte <<= 1;
  }
  // ACK 位
  setSDA(true); // 释放 SDA 线
  delay_us(1);
  setSCL(true); // 产生时钟让从设备回复 ACK
  delay_us(1);
  setSCL(false);
}
uint8_t I2C::readByte(bool ack) {
  uint8_t byte = 0;
  setSDA(true); // 释放 SDA 线准备接收数据
  for (int i = 0; i < 8; i++) {
    setSCL(true);
    byte <<= 1;
    if (getSDA())
      byte |= 0x01;
    setSCL(false);
  }
  // 发送 ACK/NACK
  setSDA(!ack);
  setSCL(true);
  delay_us(1);
  setSCL(false);
  setSDA(true); // 释放 SDA 线
  return byte;
}
void I2C::setSCL(bool level) { I2C_SCL = level; }
void I2C::setSDA(bool level) { I2C_SDA = level; }
bool I2C::getSCL() { return I2C_SCL; }
bool I2C::getSDA() { return I2C_SDA; }
