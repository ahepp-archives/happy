#ifndef HAPPY_PULSE_H
#define HAPPY_PULSE_H

#include "Timer.h"
#include "Updateable.h"

namespace happy {

struct Pulse {
    Pulse() :
        m_next(nullptr)
      , m_isOn(false)
      , m_duration(0)
    {}
    Pulse *m_next;
    bool m_isOn;
    uint32_t m_duration;
};

} // namespace happy

#endif // HAPPY_PULSE_H
