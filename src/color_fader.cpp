#include "color_fader.h"

uint8_t color_fader::steps;
uint8_t color_fader::steps_done;
float color_fader::num_per_step_r;
float color_fader::num_per_step_g;
float color_fader::num_per_step_b;
CRGB color_fader::start;
CRGB color_fader::target;

void color_fader::init(uint8_t steps_per_fade){
    if (steps_per_fade == 0)
        steps = 1;
    else 
        steps = steps_per_fade;
}

void color_fader::set_colors(CRGB a, CRGB b){
    start = a;
    target = b;
    steps_done = 0;
    num_per_step_r = start.r > target.r ?  -(1.0)*(start.r-target.r) : (float)(target.r-start.r);
    num_per_step_r /= (float) steps;

    num_per_step_g = start.g > target.g ?  -(1.0)*(start.g-target.g) : (float)(target.g-start.g);
    num_per_step_g /= (float) steps;

    num_per_step_b = start.b > target.b ? -(1.0)*(start.b-target.b) : (float)(target.b-start.b);
    num_per_step_b /= (float) steps;
}

float ssub(float a, float b, float limit = 0.0){
    return a>b ? a-b : 0.0;
}

float sadd(float a, float b, float limit = 255.0){
    return a>(255.0-b) ? 255.0 : a+b;
}

CRGB color_fader::fade(){
    CRGB res;
    if (num_per_step_r < 0){
        res.r = ssub((float)start.r, -1.0*((1+steps_done)*num_per_step_r));
    } else if (num_per_step_r > 0){
        res.r = sadd((float)start.r, ((1+steps_done)*num_per_step_r));
    }
    if (num_per_step_g < 0){
        res.g = ssub((float)start.g, -1.0*((1+steps_done)*num_per_step_g));
    } else if (num_per_step_g > 0) {
        res.g = sadd((float)start.g, ((1+steps_done)*num_per_step_g));
    }
    if (num_per_step_b < 0){
        res.b = ssub((float)start.b, -1.0*((1+steps_done)*num_per_step_b));
    } else if (num_per_step_b > 0){
        res.b = sadd((float)start.b, ((1+steps_done)*num_per_step_b));
    }

    if (steps_done >= steps) {
        return res;
    }
    steps_done++;

    return res;
}