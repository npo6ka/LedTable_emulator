#ifndef ANIMATION00_H
#define ANIMATION00_H
#include "mode.h"

#define inc_val sup_mas

class Animation00: public Mode
{
public:
    Animation00() : Mode()  {}

    byte gen_led(COLOR_TYPE *color_val)
    {
        byte val = random(0, 2);

        if (val > 0) {
            *color_val = random(0, MAX_LED_VAL);
        }
        return val;
    }

    void on_init(void)
    {
        byte i, j;

        for (i = 0; i < HOR_LED_CNT; i++) {
            for (j = 0; j < VER_LED_CNT; j++) {
                Color *cur_cl = led_get(i, j);
                //inc_val[i][j] = randInt(0, 2) << 4 | randInt(0, 2) << 2 | randInt(0, 2);
                inc_val[i][j] = gen_led(&(cur_cl->r)) << 4;
                inc_val[i][j] |= gen_led(&(cur_cl->g)) << 2;
                inc_val[i][j] |= gen_led(&(cur_cl->b));
            }
        }
    }

    byte proc_val(COLOR_TYPE *color_val, byte val) {
        int step = 2;

        if (*color_val == 0 || *color_val == MAX_LED_VAL) {
            val = 0;
        }

        if (val == 0 && random(0, 100) == 0) {
            if (*color_val > 0) {
                val = 2;
            } else {
                val = 1;
            }
        }
        if (val == 2) {
            if (*color_val < step) {
                *color_val = 0;
            } else {
                *color_val = (*color_val - step) % (MAX_LED_VAL + 1);
            }
        } else if (val == 1) {
            if (*color_val + step > MAX_LED_VAL) {
                *color_val = MAX_LED_VAL;
            } else {
                *color_val = (*color_val + step) % (MAX_LED_VAL + 1);
            }
        }

        return val & 0x3;
    }

    void on_tick(void) {
        byte i, j, buf_inc;

        for (i = 0; i < HOR_LED_CNT; i++) {
            for (j = 0; j < VER_LED_CNT; j++) {
                Color *cur_cl = led_get(i, j);
                buf_inc =  proc_val(&(cur_cl->r), (inc_val[i][j] >> 4) & 0x3) << 4;
                buf_inc |= proc_val(&(cur_cl->g), (inc_val[i][j] >> 2) & 0x3) << 2;
                buf_inc |= proc_val(&(cur_cl->b), inc_val[i][j] & 0x3);
                inc_val[i][j] = buf_inc;
            }
        }
    }
};

#undef buf_mas

#endif // ANIMATION00_H
