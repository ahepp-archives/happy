#ifndef HAPPY_PULSE_RECORDER_H
#define HAPPY_PULSE_RECORDER_H

#include "EdgeDetector.h"
#include "Pulse.h"
#include "Timer.h"
#include "Updateable.h"

namespace happy {

class PulseRecorder: public Updateable {
public:
    PulseRecorder(Pulse **, EdgeDetector &, Timer &);
    ~PulseRecorder();
    void update() override;
private:
    void addPulse(bool isOn);
    Pulse **m_head;
    Pulse *m_tail;
    Pulse *m_tmp;
    EdgeDetector &m_edge;
    Timer &m_timer;
};

} // namespace happy

#endif // HAPPY_PULSE_RECORDER_H
