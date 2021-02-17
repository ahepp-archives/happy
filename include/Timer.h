#ifndef HAPPY_TIMER_H
#define HAPPY_TIMER_H

#include <stdint.h>

namespace happy {

class Timer {
public:
    /**
     * Gets the number of ticks since the timer's construction.
     * @return The number of ticks since the timer's construction.
     */
    virtual uint32_t getTicks() = 0;
};

} // namespace happy

#endif // HAPPY_TIMER_H
