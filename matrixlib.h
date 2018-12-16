#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include "FastLED/fastled.h"

#define WIDTH 10
#define HEIGHT 10
#define LEDS_CNT WIDTH * HEIGHT
#define MAX_BRIGHTNESS 255
#define MAX_HSV 255

#define NULL nullptr
#define PROGMEM
#define random8 random

void initMatrix();

int getPixNum(int x, int y);

CRGB &getPix(int x, int y);
uint32_t getPixColor(CRGB val);
uint32_t getPixColor(int x, int y);
void setPixColor(int x, int y, CRGB color);
CRGB* getLeds(void);
uint8_t pgm_read_byte(const uint8_t *val);

void randomInit(void);
uint8_t random(void);
uint8_t random(uint8_t lim);
uint8_t random(uint8_t min, uint8_t lim);

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
