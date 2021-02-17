#ifndef HAPPY_SQUARE_WAVE_PLAYER_H
#define HAPPY_SQUARE_WAVE_PLAYER_H

#include "Dout.h"
#include "Timer.h"
#include "Updateable.h"

namespace happy {

class SquareWavePlayer : public Updateable {
public:
    SquareWavePlayer(Dout &dout , Timer &timer, int period) :
        m_dout(dout)
      , m_timer(timer)
      , m_period(period)
    {
    }
    void update() override {
        bool isSquareWaveActive = (m_timer.getTicks() / (m_period / 2)) % 2;
        m_dout.setActive(isSquareWaveActive);
    }
private:
    Dout &m_dout;
    Timer &m_timer;
    int m_period;
};

} // namespace happy

#endif // HAPPY_SQUARE_WAVE_PLAYER_H
