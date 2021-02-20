#include "pico/stdlib.h"

#include <vector>

#include "PicoDin.h"
#include "PicoDout.h"
#include "PicoI2c.h"
#include "PicoMsTimer.h"

#include "Debouncer.h"
#include "Dtee.h"
#include "Dsplit.h"
#include "Drv2605.h"
#include "Pulse.h"
#include "PulsePlayer.h"
#include "PulseRecorder.h"
#include "Updateable.h"

#include "SquareWavePlayer.h"

using namespace happy;


#define I2C_PORT i2c0
constexpr uint I2C_SDA_PIN = 16;
constexpr uint I2C_SCL_PIN = 17;

constexpr uint BUTTON_0_PIN = 15;
constexpr uint BUTTON_1_PIN = 14;
constexpr uint LED_PIN = 25;

constexpr uint32_t US_PER_MS = 1000;
constexpr uint32_t MS_PER_S  = 1000;

constexpr uint32_t DEBOUNCE_DUR_MS = 10;
constexpr uint32_t RECORD_DUR_MS = 10 * MS_PER_S;

void del(Pulse *head) {
    while(head) {
        Pulse *tmp = head;
        head = head->m_next;
        delete tmp;
    }
}

int main() {
    PicoDin b0 {BUTTON_0_PIN, false};
    PicoDin b1 {BUTTON_1_PIN, false};

    PicoDout led {LED_PIN, true};

    PicoMsTimer timer;
    Debouncer d0 {b0, timer, DEBOUNCE_DUR_MS};
    Debouncer d1 {b1, timer, DEBOUNCE_DUR_MS};
    Dtee in {d0, led}; // mirror digital input d0 state on the LED
        
    EdgeDetector e0 {in};
    EdgeDetector e1 {d1};

    PicoI2c i {I2C_PORT, I2C_SDA_PIN, I2C_SCL_PIN};
    Drv2605 driver(i);
    Dsplit out {driver, led}; // mirror digital output driver state on the LED

    Pulse *head = nullptr;
    PulseRecorder *prec = nullptr;
    PulsePlayer *pplay = nullptr;

    std::vector<Updateable*> updateables{
        &d0,
        &d1,
        &e0,
        &e1,
    };

    constexpr uint8_t STATE_WAIT   = 0;
    constexpr uint8_t STATE_RECORD = 1;
    constexpr uint8_t STATE_PLAY   = 2;
    uint8_t state = STATE_WAIT;
    uint32_t start_time = timer.getTicks();
    while (true) {
        for(auto &updateable : updateables)
            updateable->update();
        if(prec)
            prec->update();
        if(pplay)
            pplay->update();
        uint32_t time = timer.getTicks();

        uint8_t next_state = state;
        switch(state) {
            case STATE_WAIT:
                if(e1.isFallingEdge()) // button 1 released
                    next_state = STATE_RECORD;
                break;
            case STATE_RECORD:
                if(time - start_time > RECORD_DUR_MS)
                    next_state = STATE_PLAY;
                break;
            case STATE_PLAY:
                if(time - start_time > RECORD_DUR_MS)
                    next_state = STATE_WAIT;
                break;
        }
        switch(next_state) {
            case STATE_WAIT: 
                if(state == STATE_PLAY) { // entering wait
                    delete pplay;
                    pplay = nullptr;
                    del(head);
                }
                break;
            case STATE_RECORD:
                if(state == STATE_WAIT) { // entering record
                    prec = new PulseRecorder(&head, e0, timer);
                }
                break;
            case STATE_PLAY:
                if(state == STATE_RECORD) { // entering play
                    delete prec;
                    prec = nullptr;
                    pplay = new PulsePlayer(out, timer);
                    pplay->play(head);
                }
                break;
        }
        if(next_state != state)
            start_time = timer.getTicks();
        state = next_state;
    }
}
