#ifndef HAPPY_DIN_H
#define HAPPY_DIN_H

#include "Updateable.h"

namespace happy {

class Din {
public:
    virtual bool isActive() = 0;
};

} // namespace happy

#endif // HAPPY_DIN_H
