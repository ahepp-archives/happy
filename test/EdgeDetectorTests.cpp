#include "gtest/gtest.h"

#include "spdlog/spdlog.h"

#include "EdgeDetector.h"

#include "FakeButton.h"

using namespace happy;

class EdgeDetectorTests : public :: testing::Test {
protected:
    FakeButton *button;
    EdgeDetector *dut;

    void updateAll() {
        dut->update();
        if(dut->isRisingEdge())
            spdlog::debug("button has rising dut!");
        if(dut->isFallingEdge())
            spdlog::debug("button has falling dut!");
    }

    void SetUp() {
        spdlog::set_level(spdlog::level::debug);
        button = new FakeButton();
        dut = new EdgeDetector(*button);
    }
    void TearDown() {
        delete dut;
        delete button;
    }
};

TEST_F(EdgeDetectorTests, edge_detector_no_change_no_rising_edge) {
    // No rising edge is detected between two ticks with no change to the button state
    updateAll();
    updateAll();

    ASSERT_FALSE(dut->isRisingEdge());
}

TEST_F(EdgeDetectorTests, edge_detector_no_change_no_falling_edge) {
    // No falling edge is detected between two ticks with no change to the button state
    updateAll();
    updateAll();

    ASSERT_FALSE(dut->isFallingEdge());
}

TEST_F(EdgeDetectorTests, edge_detector_detects_rising_edge) {
    // A rising edge is detected the tick after a button is pressed
    updateAll();
    button->press();
    updateAll();

    ASSERT_TRUE(dut->isRisingEdge());
}

TEST_F(EdgeDetectorTests, edge_detector_detects_falling_edge) {
    // A falling edge is detected the tick after a button is released 
    button->press();
    updateAll();
    button->release();
    updateAll();

    ASSERT_TRUE(dut->isFallingEdge());
}

TEST_F(EdgeDetectorTests, edge_detector_rising_edge_expires_after_tick) {
    // A rising edge is not detected two ticks after a button is pressed (and held)
    updateAll();
    button->press();
    updateAll();
    updateAll();

    ASSERT_FALSE(dut->isRisingEdge());
}

TEST_F(EdgeDetectorTests, edge_detector_falling_edge_expires_after_tick) {
    // A falling edge is not detected two ticks after a button is released
    button->press();
    updateAll();
    button->release();
    updateAll();
    updateAll();

    ASSERT_FALSE(dut->isFallingEdge());
}
