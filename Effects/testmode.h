#pragma once

#include "Effects/effect.h"

class TestMode : public Effect
{
    uint8_t tick;

public:
    TestMode() {}
    ~TestMode() {}

    void on_init() {
        tick = 0;
    }

    void on_update(void) {
        tick = (tick + 1) % 256;

        for (uint8_t i = 0; i < HEIGHT; ++i) {
            for (uint8_t j = 0; j < WIDTH; ++j) {
                getPix(i, j) = CRGB(i * 255 / HEIGHT, i * 128 / HEIGHT + j * 128 / WIDTH,  j * 255 / WIDTH);
            }
        }
    }
};



/*#pragma once

#include "Effects/effect.h"

#define ACCURACY 100
#define MIN_VEC_SIZE 5
#define MAX_VEC_SIZE 10
#define RAINBOW_TICK_SIZE 4 //кол-во тиков до инкремента тика радуги

class TestMode : public Effect
{
    int32_t x;
    int32_t y;
    int32_t vec_x;
    int32_t vec_y;
    int tick;

    uint16_t XY( uint8_t x, uint8_t y)
    {
        return y * WIDTH + x;
    }
public:
    TestMode() {}

    void on_init() {

    }

    void on_update(void) {
        float speed = 1;

        // get some 2 random moving points
        uint8_t x2 = inoise8(millis() * speed, 25355, 685 ) / 16;
        uint8_t y2 = inoise8(millis() * speed, 355, 11685 ) / 16;

        uint8_t x3 = inoise8(millis() * speed, 55355, 6685 ) / 16;
        uint8_t y3 = inoise8(millis() * speed, 25355, 22685 ) / 16;

        // and one Lissajou function
        uint8_t x1 = beatsin8(23 * speed, 0, 15);
        uint8_t y1 = beatsin8(28 * speed, 0, 15);

        for (uint8_t y = 0; y < HEIGHT; y++) {
            for (uint8_t x = 0; x < WIDTH; x++) {
                // calculate distances of the 3 points from actual pixel
                // and add them together with weightening
                uint8_t  dx =  abs(x - x1);
                uint8_t  dy =  abs(y - y1);
                uint8_t dist = 2 * sqrt((dx * dx) + (dy * dy));

                dx =  abs(x - x2);
                dy =  abs(y - y2);
                dist += sqrt((dx * dx) + (dy * dy));

                dx =  abs(x - x3);
                dy =  abs(y - y3);
                dist += sqrt((dx * dx) + (dy * dy));

                // inverse result
                uint8_t color = 1000 / dist;

                // map color between thresholds
                if (color > 0 and color < 60) {
                  setPixColor(x, y, CHSV(color * 9, 255, 255));
                } else {
                  setPixColor(x, y, CHSV(0, 255, 255));
                }
            }
        }
    }
};
*/
