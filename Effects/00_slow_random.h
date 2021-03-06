#pragma once

#include "Effects/effect.h"

class SlowRandom : public Effect
{
    uint8_t inc_val[LEDS_CNT];
    int step;

public:
    SlowRandom() {}

    uint8_t gen_led(uint8_t &color_val)
    {
        uint8_t val = random8(2);

        if (val > 0) {
            color_val = random8();
        }

        return val;
    }

    void on_init() {
        step = 2;
        uint16_t i;

        for (i = 0; i < LEDS_CNT; i++) {
            CRGB &cur_cl = getLeds()[i];

            inc_val[i] = gen_led(cur_cl.r) << 4;
            inc_val[i] |= gen_led(cur_cl.g) << 2;
            inc_val[i] |= gen_led(cur_cl.b);
        }
    }

    void on_update() {
        uint16_t i;
        uint8_t buf;

        for (i = 0; i < LEDS_CNT; i++) {
            CRGB &cur_cl = getLeds()[i];

            buf =  proc_val(cur_cl.r, (inc_val[i] >> 4) & 0x3) << 4;
            buf |= proc_val(cur_cl.g, (inc_val[i] >> 2) & 0x3) << 2;
            buf |= proc_val(cur_cl.b, inc_val[i] & 0x3);
            inc_val[i] = buf;
        }
    }

    uint8_t proc_val(uint8_t &color_val, uint8_t val) {
            if (color_val == 0 || color_val == 255) {
                val = 0;
            }

            if (val == 0 && random8(100) == 0) {
                val = color_val == 0 ? 1 : 2;
            }
            if (val == 2) {
                if (color_val < step) {
                    color_val = 0;
                } else {
                    color_val = (color_val - step) % 256;
                }
            } else if (val == 1) {
                if (color_val + step > 255) {
                    color_val = 255;
                } else {
                    color_val = (color_val + step) % 256;
                }
            }

            return val & 0x3;
        }

};
