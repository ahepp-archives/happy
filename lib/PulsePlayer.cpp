#include "PulsePlayer.h"

namespace happy {

PulsePlayer::PulsePlayer(Dout &dout, Timer &timer) :
    m_dout(dout)
  , m_timer(timer)
  , m_head(nullptr)
  , m_mark(0)
{
}
PulsePlayer::~PulsePlayer() {
    m_dout.setActive(false);
}
void PulsePlayer::update() {
    // consume pulses that have been played
    uint32_t ticks = m_timer.getTicks();
    uint32_t elapsed = ticks - m_mark;
    while(m_head && (elapsed >= m_head->m_duration)) {
        m_mark += m_head->m_duration;
        elapsed -= m_head->m_duration;
        m_head = m_head->m_next;
        if(!m_head)
            m_dout.setActive(false);
    }

    // set output based on currently playing note
    if(m_head)
        m_dout.setActive(m_head->m_isOn);

}
void PulsePlayer::play(Pulse *head) {
    m_mark = m_timer.getTicks();
    m_head = head;
}

} // namespace happy
