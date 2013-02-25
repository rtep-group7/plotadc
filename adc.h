#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

class Adc
{
 public:
  Adc(const char *device,
      uint8_t mode,
      uint8_t bits,
      uint32_t speed,
      uint16_t dly);
  ~Adc();

  uint16_t readValue();

 private:
  int fd;
  uint8_t bits;
  uint32_t speed;
  uint16_t dly;

  void writeReset();
  void writeReg(uint8_t v);
  uint8_t readReg();
  uint16_t readData();
};

#endif // ADC_H
