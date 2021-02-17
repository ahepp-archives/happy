#include "gtest/gtest.h"

#include "spdlog/spdlog.h"

#include "Pulse.h"
#include "PulsePlayer.h"

#include "FakeButton.h"
#include "FakeHapticDriver.h"
#include "FakeTimer.h"

using namespace happy;

class PulsePlayerTests : public :: testing::Test {
protected:
    FakeTimer *timer;
    FakeHapticDriver *driver;
    PulsePlayer *dut;

    void updateAll() {
        dut->update();
    }

    void SetUp() {
        spdlog::set_level(spdlog::level::debug);
        timer = new FakeTimer();
        driver = new FakeHapticDriver();
        dut = new PulsePlayer(*driver, *timer);
    }
    void TearDown() {
        if(dut)
            delete dut;
        delete driver;
        delete timer;
    }
};

TEST_F(PulsePlayerTests, pulse_player_initially_driver_off) {
    // When the player starts, the driver is off
    updateAll();
    ASSERT_EQ(driver->isActive(), false);
}

TEST_F(PulsePlayerTests, pulse_player_null_pulse_driver_off) {
    // While the player plays a low pulse, the driver is off
    Pulse p;
    p.m_isOn = false;
    p.m_duration = 100;

    updateAll();
    timer->setTicks(50);
    updateAll();

    ASSERT_EQ(driver->isActive(), false);
}

TEST_F(PulsePlayerTests, pulse_player_pulse_driver_on) {
    // While the layer plays a high pulse, the driver is on
    Pulse p;
    p.m_isOn = true;
    p.m_duration = 100;

    dut->play(&p);
    spdlog::set_level(spdlog::level::info); // disable logspam
    for(int i = 0; i < 100; ++i) {
        timer->setTicks(i);
        updateAll();
        ASSERT_EQ(driver->isActive(), true);
    }
    spdlog::set_level(spdlog::level::debug); // reenable logging
}

TEST_F(PulsePlayerTests, pulse_player_expiring_pulse_driver_off) {
    // When a high pulse is playing, and it expires, the driver turns off
    Pulse p;
    p.m_isOn = true;
    p.m_duration = 100;

    dut->play(&p);
    updateAll();
    timer->setTicks(50);
    updateAll();
    timer->setTicks(100);
    updateAll();

    ASSERT_EQ(driver->isActive(), false);
}

TEST_F(PulsePlayerTests, pulse_player_skips_missed_pulses) {
    // When the player is updated after pulses have expired, those pulses are skipped
    Pulse p, q, r;

    p.m_isOn = true;
    p.m_duration = 25;
    p.m_next = &q;

    q.m_isOn = false;
    q.m_duration = 25;
    q.m_next = &r;

    r.m_isOn = true;
    r.m_duration = 25;


    dut->play(&p);
    updateAll();
    timer->setTicks(75);
    updateAll();

    ASSERT_EQ(driver->isActive(), false);
}
TEST_F(PulsePlayerTests, pulse_player_skips_missed_ending_pulse) {
    // When the player is updated after the last pulse has expired, the driver is off
    Pulse p;
    p.m_isOn = true;
    p.m_duration = 100;

    dut->play(&p);
    updateAll();
    timer->setTicks(101);
    updateAll();

    ASSERT_EQ(driver->isActive(), false);
}
TEST_F(PulsePlayerTests, pulse_player_destructor_turns_driver_off) {
    // When the player is destroyed, the driver is turned off
    Pulse p;
    p.m_isOn = true;
    p.m_duration = 100;

    dut->play(&p);
    updateAll();
    timer->setTicks(50);
    updateAll();

    delete dut;
    dut = nullptr;

    ASSERT_EQ(driver->isActive(), false);
}
TEST_F(PulsePlayerTests, pulse_player_initially_low_goes_high) {
    // If the pulse player starts with a low pulse, it plays subsequent high pulses
    Pulse p, q;

    p.m_isOn = false;
    p.m_duration = 25;
    p.m_next = &q;

    q.m_isOn = true;
    q.m_duration = 25;
    q.m_next = nullptr;


    dut->play(&p);
    updateAll();
    timer->setTicks(25);
    updateAll();

    ASSERT_EQ(driver->isActive(), true);
}
TEST_F(PulsePlayerTests, pulse_player_plays_note_shorter_than_elapsed_time) {
    // The pulse player plays a note with duration shorter than elapsed time
    Pulse p, q, r;
    p.m_duration = 500;
    p.m_isOn = true;
    p.m_next = &q;
    q.m_duration = 250; // this might be skipped
    q.m_isOn = false;
    q.m_next = &r;
    r.m_duration = 250;
    r.m_isOn = true;
    r.m_next = nullptr;

    dut->play(&p);
    updateAll();

    timer->setTicks(1);
    updateAll();
    ASSERT_EQ(driver->isActive(), true);

    timer->setTicks(501);
    updateAll();
    ASSERT_EQ(driver->isActive(), false); // here's the important one

    timer->setTicks(751);
    updateAll();
    ASSERT_EQ(driver->isActive(), true);

    timer->setTicks(1001);
    updateAll();
    ASSERT_EQ(driver->isActive(), false);
}
TEST_F(PulsePlayerTests, pulse_player_plays_chain) {
    // The pulse player plays a long chain of pulses
    Pulse *head = new Pulse();
    bool isOn = true;

    Pulse *tail = head;
    tail->m_duration = 250;
    tail->m_isOn = true;
    tail->m_next = new Pulse();
    tail = tail->m_next;

    tail->m_duration = 250;
    tail->m_isOn = false;
    tail->m_next = new Pulse();
    tail = tail->m_next;

    tail->m_duration = 500;
    tail->m_isOn = true;
    tail->m_next = new Pulse();
    tail = tail->m_next;

    tail->m_duration = 500;
    tail->m_isOn = false; 
    tail->m_next = new Pulse();
    tail = tail->m_next;

    tail->m_duration = 250;
    tail->m_isOn = true; 
    tail->m_next = nullptr;
    tail = tail->m_next;

    dut->play(head);
    updateAll();

    timer->setTicks(25);
    updateAll();
    ASSERT_EQ(driver->isActive(), true);

    timer->setTicks(251);
    updateAll();
    ASSERT_EQ(driver->isActive(), false);

    timer->setTicks(501);
    updateAll();
    ASSERT_EQ(driver->isActive(), true);

    timer->setTicks(1001);
    updateAll();
    ASSERT_EQ(driver->isActive(), false);

    timer->setTicks(1501);
    updateAll();
    ASSERT_EQ(driver->isActive(), true);
}
