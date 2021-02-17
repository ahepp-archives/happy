#include "gtest/gtest.h"

#include "spdlog/spdlog.h"

#include "SquareWavePlayer.h"

#include "FakeHapticDriver.h"
#include "FakeTimer.h"

using namespace happy;

class SquareWavePlayerTests : public :: testing::Test {
protected:
    FakeHapticDriver *driver;
    FakeTimer *timer;
    int period;
    SquareWavePlayer *dut;

    void SetUp() {
        spdlog::set_level(spdlog::level::debug);
        driver = new FakeHapticDriver();
        timer = new FakeTimer();
        period = 200;
        dut = new SquareWavePlayer(*driver, *timer, period);
    }
    void TearDown() {
        delete dut;
        delete timer;
        delete driver;
    }
};

TEST_F(SquareWavePlayerTests, haptic_controller_driver_starts_off) {
    ASSERT_EQ(driver->isActive(), false);
}

TEST_F(SquareWavePlayerTests, haptic_controller_driver_plays_100_tick_square_wave) {
    int test_duration = 10000;
    spdlog::set_level(spdlog::level::info); // prevent logspam from debug
    for(int i = 0; i < test_duration; ++i) {
        timer->setTicks(i);
        dut->update();
        bool isSquareWaveActive = (i / (period / 2)) % 2;
        ASSERT_EQ(driver->isActive(), isSquareWaveActive);
    }
    spdlog::set_level(spdlog::level::debug); // re-enable logging
}

