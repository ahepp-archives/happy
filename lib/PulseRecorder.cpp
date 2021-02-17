#include "PulseRecorder.h"

namespace happy {

PulseRecorder::PulseRecorder(Pulse **head, EdgeDetector &edge, Timer &timer) :
    m_head(head)
  , m_tail(nullptr)
  , m_tmp(new Pulse())
  , m_edge(edge) 
  , m_timer(timer)
{
    m_tmp->m_duration = m_timer.getTicks();
}
PulseRecorder::~PulseRecorder() {
    delete m_tmp;
}
void PulseRecorder::update() {
    if(m_edge.isRisingEdge())
        addPulse(true);
    if(m_edge.isFallingEdge())
        addPulse(false);
}
void PulseRecorder::addPulse(bool isOn) {
    int ticks = m_timer.getTicks();

    // Finish existing pulse
    m_tmp->m_duration = ticks - m_tmp->m_duration; // current - start time
    if(m_tail)
        m_tail->m_next = m_tmp;
    else
        *m_head = m_tmp; 
    m_tail = m_tmp;

    // Start new pusle
    m_tmp = new Pulse;
    m_tmp->m_duration = ticks; // store start time
    m_tmp->m_isOn = isOn;
}

} // namespace happy

