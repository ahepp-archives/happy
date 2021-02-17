#ifndef HAPPY_PICO_DRV2605_H
#define HAPPY_PICO_DRV2605_H

#include "Dout.h"

namespace happy {

class PicoDrv2605 : public Dout {
public:
    PicoDrv2605();
    ~PicoDrv2605();
    void setActive(bool isActive) override;
};

} // namespace happy

#endif // HAPPY_PICO_DRV2605_H

