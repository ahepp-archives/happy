#ifndef HAPPY_FAKE_BUTTON_H
#define HAPPY_FAKE_BUTTON_H

#include "Din.h"

namespace happy {

class FakeButton : public Din {
public:
    FakeButton() : m_input(false)
    {
    }
    bool isActive() override {
        return m_input;
    }
    void press() {
        m_input = true;
    }
    void release() {
        m_input = false;
    }
private:
    bool m_input;
};

} // namespace happy

#endif // HAPPY_FAKE_BUTTON_H
