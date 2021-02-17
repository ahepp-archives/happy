#include "gtest/gtest.h"

#include "spdlog/spdlog.h"

#include "EdgeDetector.h"
#include "PulseRecorder.h"

#include "FakeButton.h"
#include "FakeTimer.h"

using namespace happy;

class PulseRecorderTests : public :: testing::Test {
protected:
    Pulse *head;
    FakeButton *button;
    EdgeDetector *edge;
    FakeTimer *timer;
    PulseRecorder *dut;

    void updateAll() {
        edge->update();
        if(edge->isRisingEdge())
            spdlog::debug("button has rising edge!");
        if(edge->isFallingEdge())
            spdlog::debug("button has falling edge!");
        dut->update();
    }
    void printPulses() {
        Pulse *p = head;
        while(p) {
            spdlog::debug("{}/{}", p->m_isOn, p->m_duration);
            p = p->m_next;
        }
    }

    void SetUp() {
        spdlog::set_level(spdlog::level::debug);
        head = nullptr;
        button = new FakeButton();
        edge = new EdgeDetector(*button);
        timer = new FakeTimer();
        dut = new PulseRecorder(&head, *edge, *timer);
    }
    void TearDown() {
        while(head) {
            Pulse *tmp = head;
            head = head->m_next;
            delete tmp;
        }
        delete dut;
        delete edge;
        delete button;
        delete timer;
    }
};

TEST_F(PulseRecorderTests, pulse_recorder_no_button_push_no_pulses) {
    updateAll();
    timer->setTicks(100);
    updateAll();

    ASSERT_EQ(head, nullptr);
}
TEST_F(PulseRecorderTests, pulse_recorder_incomplete_button_push_null_pulse) {
    button->press();
    updateAll();
    timer->setTicks(100);
    updateAll();

    printPulses();

    ASSERT_NE(head, nullptr);
    ASSERT_EQ(head->m_duration, 0);
    ASSERT_EQ(head->m_isOn, false);
    ASSERT_EQ(head->m_next, nullptr);
}
TEST_F(PulseRecorderTests, pulse_recorder_button_push_and_release_records_pulse) {
    button->press();
    updateAll();
    timer->setTicks(100);
    button->release();
    updateAll();

    printPulses();

    ASSERT_NE(head->m_next, nullptr);
    ASSERT_EQ(head->m_next->m_duration, 100);
    ASSERT_EQ(head->m_next->m_isOn, true);
    ASSERT_EQ(head->m_next->m_next, nullptr);
}

