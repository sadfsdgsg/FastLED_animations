#pragma once
#include <stdint.h>
#include "FastLED.h"


class utils{
    public: 

        static uint8_t fade_step_single_channel(uint8_t from, uint8_t to, uint8_t step_size = 50){
            uint8_t diff = from >= to ? from - to : to - from;

            if (diff != 0){
                if (from < to)
                    from = utils::sadd8(from, step_size, to);
                else
                    from = utils::ssub8(from, step_size, to);
            }
            return from;
        }
        
        static CRGB fade_color(CRGB from, CRGB to){
            CRGB res = from;
            res.r = fade_step_single_channel(from.r, to.r);
            res.g = fade_step_single_channel(from.g, to.g);
            res.b = fade_step_single_channel(from.b, to.b);

            return res;
        }

        static uint8_t ssub8(uint8_t a, uint8_t b, uint8_t limit = 0){
            return a>b ? a-b : limit;
        }

        static uint16_t ssub16(uint16_t a, uint16_t b, uint8_t limit = 0){
            return a>b ? a-b : 0;
        }

        static uint32_t ssub32(uint32_t a, uint32_t b, uint8_t limit = 0){
            return a>b ? a-b : 0;
        }

        static uint8_t q_sadd8(uint8_t a, uint8_t b) {
            uint8_t c = a + b;
            if (c < a)  /* Can only happen due to overflow */
                c = -1;
            return c;
        }

        static uint8_t sadd8(uint8_t a, uint8_t b, uint8_t limit = 255) {
            //mostly stolen from https://stackoverflow.com/a/122288/15736460
            return (a > limit - b) ? limit : a + b;
        }

        static uint16_t sadd16(uint16_t a, uint16_t b, uint16_t limit = UINT16_MAX) {
            //mostly stolen from https://stackoverflow.com/a/122288/15736460
            return (a > limit - b) ? limit : a + b;
        }
            
        static uint32_t sadd32(uint32_t a, uint32_t b, uint32_t limit = UINT32_MAX) {
            //mostly stolen from https://stackoverflow.com/a/122288/15736460
            return (a > limit - b) ? limit : a + b;
        }
};
