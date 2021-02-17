#include "Debouncer.h"

namespace happy {

Debouncer::Debouncer(Din &din, Timer &timer, uint32_t delay) :
    m_din(din)
  , m_timer(timer)
  , m_delay(delay)
  , m_startTicks(0)
  , m_isActive(false)
  , m_last(false)
  , m_waiting(false)
{
}

bool Debouncer::isActive() {
    return m_isActive;
}
void Debouncer::update() {
    bool input = m_din.isActive();
    if(!m_waiting && (input != m_last)) {
        m_waiting = true;
        m_startTicks = m_timer.getTicks();
    }
    if(m_waiting && (m_timer.getTicks() - m_startTicks > m_delay)) {
        m_isActive = input;
        m_waiting = false;
    }
    m_last = input;
}

} // namespace happy

