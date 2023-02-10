#include "animation.h"

animation::animation(CRGB* leds, uint8_t len, uint8_t delay, uint8_t offset)
    :m_leds(leds), m_len(len), m_delay(delay), m_offset(offset){
    m_last_update = millis() - m_delay;
}

bool animation::is_due(){
    return millis() - m_last_update >= m_delay;
}

void animation::off(){
    for (uint8_t i = m_offset; i < m_len; i++)
        m_leds[i] = CRGB::Black;
}

byte animation::fade_step_single_channel(byte from, byte to, byte step_size){
    byte diff = from >= to ? from - to : to - from;

    if (diff != 0){
        if (from < to)
            from = utils::sadd8(from, step_size, to);
        else
            from = utils::ssub8(from, step_size, to);
    }
    return from;
}

void animation::set_delay(unsigned long new_delay){
    m_delay = new_delay;
}

bool animation::fade_one_step(byte i, CRGB to){
    CRGB from = m_leds[i];

    if (from.r == to.r && from.g == to.g && from.b == to.b)
        return true;
    from.r = fade_step_single_channel(from.r, to.r);
    from.g = fade_step_single_channel(from.g, to.g);
    from.b = fade_step_single_channel(from.b, to.b);

    m_leds[i] = from;

    return from.r == to.r && from.g == to.g && from.b == to.b;
}