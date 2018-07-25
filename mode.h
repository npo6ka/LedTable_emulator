#ifndef MODE_H
#define MODE_H
#include "led_lib.h"

class Mode
{
protected:
    COLOR_TYPE sup_mas[HOR_LED_CNT][VER_LED_CNT];
    int sup_val[SUP_VAL_CNT];
public:
    Mode() { on_clear(); }
    virtual void on_init(void) { }
    virtual void on_tick(void) { }
    void on_clear()
    {
        int i, j;
        for (i = 0; i < HOR_LED_CNT; ++i) {
            for (j = 0; j < VER_LED_CNT; ++j) {
                sup_mas[i][j] = 0;
            }
            sup_val[i] =0;
        }
    }
protected:
    int randInt(int low, int high)
    {
        return qrand() % ((high + 1) - low) + low;
    }
};

#endif // MODE_H
