#ifndef HAPPY_FAKE_TIMER_H
#define HAPPY_FAKE_TIMER_H

#include "Timer.h"

#include "spdlog/spdlog.h"

namespace happy {

class FakeTimer : public Timer {
public:
    FakeTimer() {
        setTicks(0);
    }
    uint32_t getTicks() override {
        return m_ticks; 
    }
    void setTicks(int ticks) {
        spdlog::debug("set timer to {}", ticks);
        m_ticks = ticks;
    }
private:
    int m_ticks;
};

}

#endif // HAPPY_FAKE_TIMER_H
