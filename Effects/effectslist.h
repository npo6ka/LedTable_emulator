#ifndef EFFECTSLIST_H
#define EFFECTSLIST_H

#include "effect.h"
#include "Effects/erroreffect.h"

class EffectsList
{
private:

    int curNum = 0;

    void setEffAmnt();

public:
    Effect *curEffect;
    int amnt;

    EffectsList();

    void setErrorEffect();
    Effect *getCurEffect();
    Effect *getEffect(int num);
    void setEffect(int num);
    int getCurEffectNum();
    void nextEffect();
    void prevEffect();
    void reloadCurEff();
};

#endif // EFFECTSLIST_H
