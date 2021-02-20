#include "PicoI2c.h"

#include "hardware/i2c.h"
#include "hardware/gpio.h"

using namespace happy;

PicoI2c::PicoI2c(i2c_inst_t *port, uint sda, uint scl) :
    m_port(port)
{
    i2c_init(m_port, 400 * 1000);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);
}

int PicoI2c::write(uint8_t addr, uint8_t *src, std::size_t len, bool noStop){
    return i2c_write_blocking(m_port, addr, src, len, noStop);
}
int PicoI2c::read(uint8_t addr, uint8_t *dst, std::size_t len, bool noStop){
    return i2c_read_blocking(m_port, addr, dst, len, noStop);
}
