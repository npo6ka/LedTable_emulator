#ifndef ANIMATION01_H
#define ANIMATION01_H

#include "mode.h"

#define lenght sup_val[0]
#define cur_drib sup_mas[0]

class Animation01: public Mode
{
public:
    Animation01() : Mode()  {}

    void on_init(void)
    {
        lenght = 12;
    }

    void on_tick(void) {
        for (int i = 0; i < HOR_LED_CNT;  ++i) {
            if (cur_drib[i] == 0 && random(0, 40) == 0) {
                cur_drib[i] = 1;
            } else if (cur_drib[i] != 0) {
                cur_drib[i] += 1;
                if (cur_drib[i] >= lenght + VER_LED_CNT) {
                    cur_drib[i] = 0;
                }
            }
        }

        int step = MAX_LED_VAL / lenght;

        for (int i = 0; i < HOR_LED_CNT;  ++i) {
            for (int j = 0; j < VER_LED_CNT;  ++j) {
                if (j < cur_drib[i] && cur_drib[i] != 0) {
                    led_set(i, j, 0, 0, std::max((int) (MAX_LED_VAL - (cur_drib[i] - j - 1) * step), 0), SET);
                } else {
                    led_set(i, j, 0, 0, 0, SET);
                }
            }
        }
    }
};

#undef lenght
#undef cur_drib

#endif // ANIMATION01_H
