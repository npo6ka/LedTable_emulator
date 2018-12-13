#pragma once

#include "Effects/effect.h"

class SimpleRainbow : public Effect
{
    int tick = 0;
    int phaseShift = 10;

public:
    SimpleRainbow() {}

    void on_tick() {
        uint8_t x, y;
        tick = tick % (MAX_HSV + 1);

        for (x = 0; x < 10; x++) {
            for (y = 0; y < 10; y++) {
                getPix(x, y) = CHSV((tick + x + y * phaseShift / 2) % (MAX_HSV + 1), 255, 255);
            }
        }

        tick += 1;
    }
};
