#ifndef HAPPY_FAKE_HAPTIC_DRIVER_H
#define HAPPY_FAKE_HAPTIC_DRIVER_H

#include "Din.h"
#include "Dout.h"

#include "spdlog/spdlog.h"

namespace happy {

class FakeHapticDriver : public Din, public Dout {
public:
    FakeHapticDriver() : m_isActive(false) {
        setActive(false);
    }
    virtual ~FakeHapticDriver() {
        setActive(false);
    }
    void setActive(bool isActive) override {
        spdlog::debug("set driver: {} -> {}", m_isActive, isActive);
        m_isActive = isActive;
    }
    bool isActive() override {
        return m_isActive;
    }
private:
    bool m_isActive;
};

}

#endif // HAPPY_FAKE_HAPTIC_DRIVER_H
