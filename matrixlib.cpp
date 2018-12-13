#include "matrixlib.h"
#include <QDebug>

static CRGB leds[LEDS_CNT];

void initMatrix() {
    if (WIDTH < 0 || WIDTH > 0xff || HEIGHT < 0 || HEIGHT > 0xff) {
        qDebug("Value out of range in function initMatrix", WIDTH, HEIGHT);
    }
    FastLED.addLeds(leds, LEDS_CNT).setCorrection( TypicalLEDStrip );
}

int getPixNum(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug("Value out of range in function getPixNum", x, y);
    }

    return (WIDTH * HEIGHT - (y * WIDTH + x + 1));
}

CRGB &getPix(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug("Value out of range in function getPix", x, y);
        return leds[0];
    }

    return leds[getPixNum(x, y)];
}

uint32_t getPixColor(CRGB val) {
    return (((uint32_t)val.r << 16) | ((uint16_t)val.g << 8 ) | val.b);
}

uint32_t getPixColor(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug("Value out of range in function getPixColor", x, y);
        return 0;
    }

    return getPixColor(getPix(x, y));
}

void setPixColor(int x, int y, uint32_t color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug("Value out of range in function setPixColor", x, y);
    }

    getPix(x, y) = color;
}

CRGB* getLeds(void) {
    return leds;
}
