#ifndef ERROREVENT_H
#define ERROREVENT_H

#include "Effects/effect.h"

class ErrorEffect : public Effect
{
public:
    ErrorEffect() {}

    void on_tick() {

    }

    void on_update() {
        FastLED.showColor(CRGB::Red);
    }
};

#endif // 00SLOWRANDOM_H
