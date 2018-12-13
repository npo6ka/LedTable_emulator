#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include "FastLED/fastled.h"

#define WIDTH 10
#define HEIGHT 10
#define LEDS_CNT WIDTH * HEIGHT
#define MAX_BRIGHTNESS 255
#define MAX_HSV 255

#define NULL nullptr

void initMatrix();

int getPixNum(int x, int y);

CRGB &getPix(int x, int y);
uint32_t getPixColor(CRGB val);
uint32_t getPixColor(int x, int y);
void setPixColor(int x, int y, uint32_t color);
CRGB* getLeds(void);

template <typename T>
const T & max(const T & value1, const T & value2) {
    return (value1 > value2) ? value1 : value2;
}

template <typename T>
const T & min(const T & value1, const T & value2) {
    return (value1 < value2) ? value1 : value2;
}


#endif // MATRIXLIB_H
