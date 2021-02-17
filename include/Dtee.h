#ifndef HAPPY_DTEE_H
#define HAPPY_DTEE_H

#include "Din.h"
#include "Dout.h"

namespace happy {

class Dtee : public Din {
public:
    Dtee(Din &in, Dout &out) : m_in(in), m_out(out) {
    }
    bool isActive() override {
        bool tmp = m_in.isActive();
        m_out.setActive(tmp);
        return tmp;
    }
private:
    Din &m_in;
    Dout &m_out;
};

} // namespace happy

#endif // HAPPY_DTEE_H
