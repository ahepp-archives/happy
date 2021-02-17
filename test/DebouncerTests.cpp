#include "gtest/gtest.h"

#include "spdlog/spdlog.h"

#include "Debouncer.h"

#include "FakeButton.h"
#include "FakeTimer.h"

using namespace happy;

class DebouncerTests : public :: testing::Test {
protected:
    FakeButton *button;
    FakeTimer *timer;
    Debouncer *dut;
    uint32_t bounceDelay;

    void updateAll() {
        dut->update();
    }

    void SetUp() {
        bounceDelay = 100;
        spdlog::set_level(spdlog::level::debug);
        button = new FakeButton();
        timer = new FakeTimer();
        dut = new Debouncer(*button, *timer, bounceDelay);
    }
    void TearDown() {
        delete dut;
        delete timer;
        delete button;
    }
};

TEST_F(DebouncerTests, debouncer_initially_off) {
    // Debouncer stays off while button is off
    spdlog::set_level(spdlog::level::info); // disable logspam
    for(int i = 0; i < 1000; ++i) {
        timer->setTicks(i);
        updateAll();
        ASSERT_EQ(dut->isActive(), false);
    }
    spdlog::set_level(spdlog::level::debug); // reenable logging
}

TEST_F(DebouncerTests, debouncer_activates_after_delay) {
    // Debouncer turns on delay ticks after the button is held
    button->press();

    spdlog::set_level(spdlog::level::info); // disable logspam
    for(int i = 0; i < 100; ++i) {
        timer->setTicks(i);
        updateAll();
        ASSERT_EQ(dut->isActive(), false);
    }
    spdlog::set_level(spdlog::level::debug); // reenable logging

    timer->setTicks(101);
    updateAll();

    ASSERT_EQ(dut->isActive(), true);
}

TEST_F(DebouncerTests, debouncer_activates_after_delay_with_bounces) {
    // Debouncer turns on delay ticks after the button is held
    button->press();
    updateAll();

    spdlog::set_level(spdlog::level::info); // disable logspam
    for(int i = 1; i < 50; ++i) {
        if(button->isActive())
            button->release();
        else
            button->press();
        timer->setTicks(i);
        updateAll();
        ASSERT_EQ(dut->isActive(), false);
    }
    spdlog::set_level(spdlog::level::debug); // reenable logging

    button->press();
    timer->setTicks(51);
    updateAll();

    timer->setTicks(101);
    updateAll();

    ASSERT_EQ(dut->isActive(), true);
}

// button held for uint max ticks rolls over correctly
TEST_F(DebouncerTests, debouncer_activates_on_rollover) {
    // Debouncer activates after delay when wait spans timer rollover
    button->press();
    timer->setTicks(UINT32_MAX - 50);
    updateAll();

    timer->setTicks(51);
    updateAll();

    ASSERT_EQ(dut->isActive(), true);
}
