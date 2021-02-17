#include "PicoMsTimer.h"
#include "hardware/timer.h"

using namespace happy;

PicoMsTimer::PicoMsTimer() {
}
PicoMsTimer::~PicoMsTimer() {
}
uint32_t PicoMsTimer::getTicks() {
    return (uint32_t) (time_us_64() / 1000);
}
