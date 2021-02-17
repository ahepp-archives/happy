#ifndef HAPPY_PICO_DIN_H
#define HAPPY_PICO_DIN_H

#include "Din.h"

namespace happy {

class PicoDin : public Din {
public:
    PicoDin(unsigned int pin, bool isActiveHigh);
    ~PicoDin();
    bool isActive() override;
private:
    unsigned int m_pin;
    bool m_isActiveHigh;
};

} // namespace happy 

#endif // HAPPY_PICO_DIN_H
