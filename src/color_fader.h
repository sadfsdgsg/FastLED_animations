#pragma once 

#include "FastLED.h"
#include "stdlib.h"

class color_fader{
    public:
        static void init(uint8_t steps_per_fade);
        static void set_colors(CRGB start, CRGB target);
        static CRGB fade();

    private:
        static uint8_t steps;
        static uint8_t steps_done;
        static float num_per_step_r;
        static float num_per_step_g;
        static float num_per_step_b;
        static CRGB start;
        static CRGB target;
};