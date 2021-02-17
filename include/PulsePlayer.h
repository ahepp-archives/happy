#ifndef HAPPY_PULSE_PLAYER_H
#define HAPPY_PULSE_PLAYER_H

#include "Dout.h"
#include "Timer.h"
#include "Pulse.h"
#include "Updateable.h"

namespace happy {

class PulsePlayer : public Updateable {
public:
    PulsePlayer(Dout &, Timer &);
    ~PulsePlayer();
    void update() override;
    void play(Pulse *);
private:
    Dout &m_dout;
    Timer &m_timer;
    Pulse *m_head;
    int m_mark;
};

} // namespace happy

#endif // HAPPY_PULSE_PLAYER_H

