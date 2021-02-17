#include "gtest/gtest.h"

#include "spdlog/spdlog.h"

#include "FakeTimer.h"
#include "FakeHapticDriver.h"

using namespace happy;

class FakeTimerTests: public ::testing::Test {
protected:
    FakeTimer *timer;

    void SetUp() {
        spdlog::set_level(spdlog::level::debug);
        timer = new FakeTimer();
    }
    void TearDown() {
        if(timer)
            delete timer;
    }
};

TEST_F(FakeTimerTests, fake_timer_initially_zero_ticks) {
    ASSERT_EQ(timer->getTicks(), 0);
}

TEST_F(FakeTimerTests, fake_timer_returns_set_ticks) {
    timer->setTicks(100);
    ASSERT_EQ(timer->getTicks(), 100);
}

class FakeHapticDriverTests : public ::testing::Test {
protected:
    FakeHapticDriver *driver;

    void SetUp() {
        spdlog::set_level(spdlog::level::debug);
        driver = new FakeHapticDriver();
    }
    void TearDown() {
        if(driver)
            delete driver;
    }
};

TEST_F(FakeHapticDriverTests, fake_haptic_driver_initially_off) {
    ASSERT_EQ(driver->isActive(), false);
}
TEST_F(FakeHapticDriverTests, fake_haptic_driver_turns_on) {
    driver->setActive(true);

    ASSERT_EQ(driver->isActive(), true);
}
TEST_F(FakeHapticDriverTests, fake_haptic_driver_turns_off) {
    driver->setActive(true);
    driver->setActive(false);

    ASSERT_EQ(driver->isActive(), false);
}
