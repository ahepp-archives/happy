#ifndef HAPPY_DSPLIT_H
#define HAPPY_DSPLIT_H

#include "Dout.h"

namespace happy {

class Dsplit : public Dout {
public:
    Dsplit(Dout &a, Dout &b) : m_a(a), m_b(b) {
    }
    void setActive(bool isActive) override {
        m_a.setActive(isActive);
        m_b.setActive(isActive);
    }
private:
    Dout &m_a;
    Dout &m_b;
};

} // namespace happy

#endif // HAPPY_DSPLIT_H
