#pragma once

#include "animation.h"
#include "utils.h"

class knightrider: public animation{
public:
    knightrider(CRGB* leds, byte len, byte delay, byte offset, byte width = 3, CRGB color = CRGB::Red, CRGB bg_color = CRGB::Black);
    void init();
    bool maintain();
    void set_colors(CRGB effect, CRGB background);

private:
    CRGB m_color, m_bg_color;
    uint8_t m_pos, m_width;
    int8_t m_dir;
};