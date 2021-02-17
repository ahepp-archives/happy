#include "PicoDout.h"

#include "hardware/gpio.h"

using namespace happy;

PicoDout::PicoDout(unsigned int pin, bool isActiveHigh) :
    m_pin(pin)
  , m_isActiveHigh(isActiveHigh)
{
    gpio_init(m_pin);
    gpio_set_dir(m_pin, GPIO_OUT);
}
PicoDout::~PicoDout() {
    // TODO
}
void PicoDout::setActive(bool isActive) {
    gpio_put(m_pin, m_isActiveHigh == isActive);
}

