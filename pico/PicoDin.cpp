#include "PicoDin.h"

#include "hardware/gpio.h"

using namespace happy;

PicoDin::PicoDin(unsigned int pin, bool isActiveHigh) :
    m_pin(pin)
  , m_isActiveHigh(isActiveHigh)
{
    gpio_init(m_pin);
    gpio_set_dir(m_pin, GPIO_IN);
    if(m_isActiveHigh)
        gpio_pull_down(m_pin);
    else
        gpio_pull_up(m_pin);
}
PicoDin::~PicoDin() {
    // TODO
}
bool PicoDin::isActive() {
    return m_isActiveHigh == gpio_get(m_pin);
}

