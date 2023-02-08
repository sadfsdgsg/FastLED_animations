#include <FastLED.h>
#include "color_fader.h"

// How many leds in your strip?
#define NUM_LEDS 24

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 4

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB currentColor;
CRGB targetColor;
uint8_t state = 0;

void fade(CRGB target, uint8_t steps = 100){
  unsigned long start = millis();
  color_fader::init(steps);
  color_fader::set_colors(currentColor, target);
  for (int i = 0; i <= steps; i++){
    currentColor = color_fader::fade();
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = currentColor;
    FastLED.show();
    //delay(0);
  }
  Serial.printf("fade done... %hhu steps in %lums\r\n", steps, millis()-start);
}

void setup() { 
  Serial.begin(115200);
  delay(500);
  Serial.println();
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(255);
  currentColor = CRGB::Pink;
  Serial.println("yay");
}

void loop() {
  Serial.println("g");
  fade(CRGB::Green);
  Serial.println("done");
  delay(1000);

  Serial.println("r");
  fade(CRGB::Red);
  Serial.println("done");
  delay(1000);

  Serial.println("b");
  fade(CRGB::Blue);
  Serial.println("done");
  delay(1000);
}