#ifndef EFFECT_H
#define EFFECT_H

#include "QTime"
#include "matrixlib.h"

class Effect
{
public:
    Effect() { }
    virtual void on_tick() = 0;
    virtual void on_init() {}
    virtual void show() {
        FastLED.show();
    }
};

#endif // EFFECT_H
