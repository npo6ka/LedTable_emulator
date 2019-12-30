#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include "FastLED/FastLED.h"

#define WIDTH 16
#define HEIGHT 16
#define LEDS_CNT WIDTH * HEIGHT
#define MAX_BRIGHTNESS 255
#define MAX_HSV 255

//#define NULL nullptr
#define PROGMEM
#define random random8

void initMatrix();

int getPixNum(const uint8_t x, const uint8_t y);

CRGB &getPix(const uint8_t x, const uint8_t y);
uint32_t getPixColor(CRGB val);
uint32_t getPixColor(const uint8_t x, const uint8_t y);
void setPixColor(const uint8_t x, const uint8_t y, CRGB color);
CRGB* getLeds(void);
uint8_t pgm_read_byte(const uint8_t *val);

void randomInit(void);
// uint8_t random(void);
// uint8_t random(uint8_t lim);
// uint8_t random(uint8_t min, uint8_t lim);

void fader(uint8_t step);
void fadePix(uint8_t x, uint8_t y, uint8_t step);

void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, CRGB color);

template <typename T>
const T & max(const T & value1, const T & value2) {
    return (value1 > value2) ? value1 : value2;
}

template <typename T>
const T & min(const T & value1, const T & value2) {
    return (value1 < value2) ? value1 : value2;
}


#endif // MATRIXLIB_H
