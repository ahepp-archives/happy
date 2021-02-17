#ifndef HAPPY_EDGE_DETECTOR_H
#define HAPPY_EDGE_DETECTOR_H

#include "Din.h"
#include "Updateable.h"

namespace happy {

class EdgeDetector : public Updateable {
public:
    EdgeDetector(Din &);
    bool isRisingEdge();
    bool isFallingEdge();
    void update() override;
private:
    bool m_last;
    bool m_pressed;
    Din &m_din;
};

} // namespace happy

#endif // HAPPY_EDGE_DETECTOR_H

