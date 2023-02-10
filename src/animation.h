#pragma once

#include "FastLED.h"
#include <stdint.h>
#include "utils.h"

class animation{
public:
    /*
    leds = pointer zu led Array
    len = Anzahl der LEDS
    delay = aktualisierung alle x ms
    offset = falls strip nicht bei 0 anfängt
    */
    animation (CRGB* leds, uint8_t len, uint8_t delay, uint8_t offset);
    virtual void init() = 0;
    /**
     * returns if a full cycle is done.
    */
    virtual bool maintain() = 0;
    /**
     * Todo: change to set_fps
    */
    void set_delay(unsigned long new_delay);
    void off();

protected:
    uint8_t fade_step_single_channel(uint8_t from, uint8_t to, uint8_t step_size = 50);
    bool is_due();
    bool fade_one_step(uint8_t i, CRGB to);
    CRGB* m_leds;
    uint8_t m_len;
    unsigned long m_last_update;
    uint8_t m_delay;
    uint8_t m_offset;
};