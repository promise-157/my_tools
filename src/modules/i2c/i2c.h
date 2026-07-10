/*
 * @Author: promise-157 1579834017@qq.com
 * @Date: 2026-05-10 20:27:30
 * @LastEditors: promise-157 1579834017@qq.com
 * @LastEditTime: 2026-05-11 22:19:22
 * @FilePath: /imx6ull_lab/home/promise/my_tools/src/modules/i2c/i2c.h
 * @Description:
 *旨在写一个完全由代码实现的软件I2C而非传统的调用各平台提供的库函数。练手作用。
 * Copyright (c) 2026 by ${git_name_email}, All Rights Reserved.
 */
#ifndef I2C_H
#define I2C_H
#include <stdint.h>

class I2C {
public:
  I2C();
  void start();
  void stop();
  void writeByte(uint8_t byte);
  uint8_t readByte(bool ack);
  void setSCL(bool level);
  void setSDA(bool level);
  bool getSCL();
  bool getSDA();

private:
  bool I2C_SCL;
  bool I2C_SDA;
};
#endif // I2C_H
