#include "matrixlib.h"
#include <QDebug>
#include "QTime"

static CRGB leds[LEDS_CNT];

void initMatrix() {
    if (WIDTH < 0 || WIDTH > 0xff || HEIGHT < 0 || HEIGHT > 0xff) {
        qDebug() << "Value out of range in function initMatrix" << WIDTH << HEIGHT;
    }
    FastLED.addLeds(leds, LEDS_CNT).setCorrection( TypicalLEDStrip );
}

int getPixNum(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug() <<"Value out of range in function getPixNum" << x << y;
    }

    return (WIDTH * HEIGHT - (y * WIDTH + x + 1));
}

CRGB &getPix(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug() << "Value out of range in function getPix" << x << y;
        return leds[0];
    }

    return leds[getPixNum(x, y)];
}

uint32_t getPixColor(CRGB val) {
    return (((uint32_t)val.r << 16) | ((uint16_t)val.g << 8 ) | val.b);
}

uint32_t getPixColor(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug() << "Value out of range in function getPixColor" << x << y;
        return 0;
    }

    return getPixColor(getPix(x, y));
}

void setPixColor(int x, int y, CRGB color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        qDebug() << "Value out of range in function setPixColor" << x << y;
        return;
    }

    getPix(x, y) = color;
}

CRGB* getLeds(void) {
    return leds;
}

uint8_t pgm_read_byte(const uint8_t *val) {
    return *val;
}

void randomInit() {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

uint8_t random() {
    return qrand() % 255;
}

uint8_t random(uint8_t lim) {
    uint8_t r = random();
    r = (r*lim) >> 8;
    return r;
}

uint8_t random(uint8_t min, uint8_t lim) {
    uint8_t delta = lim - min;
    uint8_t r = random(delta) + min;
    return r;
}

void fader(uint8_t step) {
  for (uint8_t i = 0; i < WIDTH; i++) {
    for (uint8_t j = 0; j < HEIGHT; j++) {
      fadePix(i, j, step);
    }
  }
}

void fadePix(uint8_t x, uint8_t y, uint8_t step) {
    CRGB pixelNum = getPix(x, y);
    if (!pixelNum) return;

    if (pixelNum.r >= 30 ||
        pixelNum.g >= 30 ||
        pixelNum.b >= 30) {
        pixelNum.fadeToBlackBy(step);
    } else {
        pixelNum = 0;
    }
    setPixColor(x, y, pixelNum);
}

void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, CRGB color)
{
    uint8_t deltaX = abs((int16_t)x2 - x1);
    uint8_t deltaY = abs((int16_t)y2 - y1);
    int8_t signX = x1 < x2 ? 1 : -1;
    int8_t signY = y1 < y2 ? 1 : -1;

    int16_t error = deltaX - deltaY;
    int32_t error2;

    setPixColor(x2, y2, color);
    while (x1 != x2 || y1 != y2) {
        setPixColor(x1, y1, color);
        error2 = error * 2;

        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}
