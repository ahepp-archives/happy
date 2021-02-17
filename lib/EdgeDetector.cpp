#include "EdgeDetector.h"

namespace happy {

EdgeDetector::EdgeDetector(Din &din) : m_last(false), m_pressed(false), m_din(din)
{
}

bool EdgeDetector::isRisingEdge() {
    return m_din.isActive() && !m_last;
}
bool EdgeDetector::isFallingEdge() {
    return !m_din.isActive() && m_last;
}
void EdgeDetector::update() {
    m_last = m_pressed;
    m_pressed = m_din.isActive();
}

} // namespace happy

