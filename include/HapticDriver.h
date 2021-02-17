#ifndef HAPPY_HAPTIC_DRIVER_H
#define HAPPY_HAPTIC_DRIVER_H

namespace happy {

/**
 * An interface for haptic motor drivers.
 * Prior to the first call to `on`, the driver shall not be running.
 * After destruction of the object, the driver shall not be running.
 */
class HapticDriver{
public:
    /**
     * Sets the haptic driver to run continuously
     * @post The driver shall be running.
     */
    virtual void on() = 0;
    /**
     * Sets the haptic motor to stop running.
     * @post The driver shall not be running.
     */
    virtual void off() = 0;
};


} // namespace happy

#endif // HAPPY_HAPTIC_DRIVER_H
