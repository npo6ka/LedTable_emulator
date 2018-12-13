#pragma once

#include "Effects/effect.h"

class Dribs : public Effect
{
    uint8_t cur_drib[WIDTH];
    uint8_t lenght = 12;

public:
    Dribs() {}

    void on_init() {

    }

    void on_tick() {
        for (int i = 0; i < WIDTH;  ++i) {
            if (cur_drib[i] == 0 && random8(40) == 0) {
                cur_drib[i] = 1;
            } else if (cur_drib[i] != 0) {
                cur_drib[i] += 1;
                if (cur_drib[i] >= lenght + HEIGHT) {
                    cur_drib[i] = 0;
                }
            }
        }

        int step = MAX_BRIGHTNESS / lenght;
        for (int i = 0; i < WIDTH;  ++i) {
            for (int j = 0; j < HEIGHT;  ++j) {
                if (j < cur_drib[i]  && cur_drib[i] != 0) {
                    getPix(i, j) = CRGB(0, 0, max(MAX_BRIGHTNESS - (cur_drib[i] - j - 1) * step, 0));
                } else {
                    getPix(i, j) = 0x0;
                }
            }
            //outln();
        }
    }
};
