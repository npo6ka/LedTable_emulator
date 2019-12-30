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