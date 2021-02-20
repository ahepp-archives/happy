#ifndef HAPPY_DRV2605_H
#define HAPPY_DRV2605_H

#include "Dout.h"
#include "I2c.h"

namespace happy {

class Registers {
public:
    Registers(uint8_t deviceAddr, I2c &i2c) :
        m_deviceAddr(deviceAddr)
      , m_i2c(i2c)
    {
    }
    void write(uint8_t reg_addr, uint8_t val) {
        uint8_t buf[] = {reg_addr, val};
        m_i2c.write(m_deviceAddr, buf, 2, false);
    }
    uint8_t read(uint8_t reg_addr) {
        uint8_t val;
        m_i2c.write(m_deviceAddr, &reg_addr, 1, true);
        m_i2c.read(m_deviceAddr, &val, 1, false);
        return val;
    }
private:
    uint8_t m_deviceAddr;
    I2c &m_i2c;
};

class Drv2605 : public Dout {
public:
    Drv2605(I2c &i2c);
    ~Drv2605();
    void setActive(bool isActive) override;
private:
    Registers m_reg;
};

} // namespace happy

#endif // HAPPY_DRV2605_H

