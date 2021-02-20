#ifndef HAPPY_PICO_I2C_H
#define HAPPY_PICO_I2C_H

#include "I2c.h"
#include "hardware/i2c.h"

namespace happy {

class PicoI2c : public I2c{
public:
    PicoI2c(i2c_inst_t *port, uint sda, uint scl);
    int write(uint8_t addr, uint8_t *src, std::size_t len, bool noStop) override;
    int read(uint8_t addr, uint8_t *dst, std::size_t len, bool noStop) override;
private:
    i2c_inst_t *m_port;
};

} // namespace happy

#endif // HAPPY_PICO_I2C_H

