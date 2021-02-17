#ifndef HAPPY_PICO_MS_TIMER_H
#define HAPPY_PICO_MS_TIMER_H

#include "Timer.h"

namespace happy {

class PicoMsTimer : public Timer {
public:
    PicoMsTimer();
    ~PicoMsTimer();
    uint32_t getTicks() override;
};

} // happy

#endif // HAPPY_PICO_MS_TIMER_H
