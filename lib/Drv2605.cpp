#include "Drv2605.h"
#include "Drv2605Defs.h"
#include "I2c.h"

using namespace happy;

#define I2C_ADDR 0x5A

Drv2605::Drv2605(I2c &i2c) :
    m_reg(I2C_ADDR, i2c)
{
    volatile uint8_t id = m_reg.read(DRV2605_REG_STATUS);
  
    m_reg.write(DRV2605_REG_MODE,       0x00);
    m_reg.write(DRV2605_REG_WAVESEQ1,      1);
    m_reg.write(DRV2605_REG_WAVESEQ2,      0);
    m_reg.write(DRV2605_REG_LIBRARY,       1);
    m_reg.write(DRV2605_REG_OVERDRIVE,     0);
    m_reg.write(DRV2605_REG_SUSTAINPOS,    0);
    m_reg.write(DRV2605_REG_SUSTAINNEG,    0);
    m_reg.write(DRV2605_REG_BREAK,         0);
    m_reg.write(DRV2605_REG_AUDIOMAX,   0x64);
  
    // ERM open loop
    m_reg.write(DRV2605_REG_FEEDBACK, m_reg.read(DRV2605_REG_FEEDBACK) & 0x7F);
    m_reg.write(DRV2605_REG_CONTROL3, m_reg.read(DRV2605_REG_CONTROL3) | 0x20);

    // Go!
    m_reg.write(DRV2605_REG_MODE, DRV2605_MODE_REALTIME);
}

Drv2605::~Drv2605() {
    setActive(false);
}

void Drv2605::setActive(bool isActive) {
    if(isActive)
        m_reg.write(DRV2605_REG_RTPIN, 100);
    else
        m_reg.write(DRV2605_REG_RTPIN, 0);
}
