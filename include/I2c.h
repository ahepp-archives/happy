#ifndef HAPPY_I2C_H
#define HAPPY_I2C_H

#include <stddef.h>
#include <stdint.h>

class I2c {
public:
    virtual int write(uint8_t addr, uint8_t *src, size_t len, bool noStop) = 0;
    virtual int read(uint8_t addr, uint8_t *dst, size_t len, bool noStop) = 0;
};

#endif // HAPPY_I2C_H
