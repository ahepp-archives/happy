#include "PicoDrv2605.h"
#include "Drv2605.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#define I2C_PORT i2c0
#define I2C_ADDR 0x5A

using namespace happy;

constexpr uint I2C_SDA_PIN = 16;
constexpr uint I2C_SCL_PIN = 17;

static void write_reg(uint8_t reg_addr, uint8_t val) {
    uint8_t buf[] = {reg_addr, val};
    i2c_write_blocking(I2C_PORT, I2C_ADDR, buf, 2, false);
}
static uint8_t read_reg(uint8_t reg_addr) {
    uint8_t val;
    i2c_write_blocking(I2C_PORT, I2C_ADDR, &reg_addr, 1, true);
    i2c_read_blocking(I2C_PORT, I2C_ADDR, &val, 1, false);
    return val;
}

PicoDrv2605::PicoDrv2605() {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    volatile uint8_t id = read_reg(DRV2605_REG_STATUS);
  
    write_reg(DRV2605_REG_MODE,       0x00);
    write_reg(DRV2605_REG_WAVESEQ1,      1);
    write_reg(DRV2605_REG_WAVESEQ2,      0);
    write_reg(DRV2605_REG_LIBRARY,       1);
    write_reg(DRV2605_REG_OVERDRIVE,     0);
    write_reg(DRV2605_REG_SUSTAINPOS,    0);
    write_reg(DRV2605_REG_SUSTAINNEG,    0);
    write_reg(DRV2605_REG_BREAK,         0);
    write_reg(DRV2605_REG_AUDIOMAX,   0x64);
  
    // ERM open loop
    write_reg(DRV2605_REG_FEEDBACK, read_reg(DRV2605_REG_FEEDBACK) & 0x7F);
    write_reg(DRV2605_REG_CONTROL3, read_reg(DRV2605_REG_CONTROL3) | 0x20);

    // Go!
    write_reg(DRV2605_REG_MODE,       DRV2605_MODE_REALTIME);
}

PicoDrv2605::~PicoDrv2605() {
    setActive(false);
}

void PicoDrv2605::setActive(bool isActive) {
    if(isActive)
        write_reg(DRV2605_REG_RTPIN, 100);
    else
        write_reg(DRV2605_REG_RTPIN, 0);
}
