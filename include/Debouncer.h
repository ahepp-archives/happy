#ifndef HAPPY_DEBOUNCER_H
#define HAPPY_DEBOUNCER_H

#include "Din.h"
#include "Timer.h"
#include "Updateable.h"

namespace happy {

class Debouncer : public Din, public Updateable {
public:
    Debouncer(Din &, Timer &, uint32_t);
    bool isActive() override;
    void update() override;
private:
    Din &m_din;
    Timer &m_timer;
    uint32_t m_delay;
    uint32_t m_startTicks;
    bool m_isActive;
    bool m_last;
    bool m_waiting;
};

} // namespace happy

#endif // HAPPY_DEBOUNCER_H

