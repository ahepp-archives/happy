#ifndef HAPPY_PICO_DOUT_H
#define HAPPY_PICO_DOUT_H

#include "Dout.h"

namespace happy {

class PicoDout : public Dout {
public:
    PicoDout(unsigned int pin, bool isActiveHigh);
    ~PicoDout();
    void setActive(bool isActive) override;
private:
    unsigned int m_pin;
    bool m_isActiveHigh;
};

} // namespace happy 

#endif // HAPPY_PICO_DOUT_H
