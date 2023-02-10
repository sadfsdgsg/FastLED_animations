#include "knightrider.h"


knightrider::knightrider(CRGB* leds, byte len, byte delay, byte offset, byte width, CRGB color, CRGB bg_color)
        : animation(leds, len, delay, offset) {
    m_width = width < m_offset+m_len ? width : m_offset+m_len - 1;
    m_width = width > 0 ? width : 1;
    m_color = color;
    m_bg_color = bg_color;
    m_pos = m_offset;
    m_dir = 1;
}

void knightrider::init(){
    if (m_dir > 0){
        for (byte i = m_offset; i < m_offset+m_width; i++){
            m_leds[i] = m_color;
            FastLED.show();
            delay(m_delay);
        }
        for (byte i = m_offset+m_width; i < m_len; i++){
            m_leds[i] = m_bg_color;
            FastLED.show();
            delay(m_delay);
        }
    }
    m_last_update = millis();
}

bool knightrider::maintain(){
    if (!is_due()) return false;

    byte upper = utils::sadd8(m_offset, m_pos);
    byte lower = utils::sadd8(upper, m_width);

    bool tail = true, head = true;
    if (m_dir > 0){
        tail = fade_one_step(upper, m_bg_color);
        head = fade_one_step(lower, m_color);
    } else if (m_dir < 0){
        head = fade_one_step(upper, m_color);
        tail = fade_one_step(lower, m_bg_color);
    }
    
    if (!head && !tail){
        m_last_update = millis() - (m_delay/10);
        return false;
    }
    
    m_last_update = millis();
    
    if (m_pos + m_dir < m_offset){
        m_dir = -m_dir;
        return true;
    } else if (m_pos + m_width + m_dir >= m_len){
        m_dir = -m_dir;
    } else {
        m_pos += m_dir;
    }
    return false;
}

void knightrider::set_colors(CRGB effect, CRGB background){
    m_color = effect;
    m_bg_color = background;
}