#ifndef EFFECTSLIST_H
#define EFFECTSLIST_H

#include "effect.h"
#include "erroreffect.h"

class EffectsList
{
private:

    int curNum = 0;

    void init();

public:
    Effect *curEffect;
    int amnt;

    EffectsList();

    void setErrorEffect();
    Effect *getCurEffect();
    Effect *getNewEffectInstance(int num);
    void clearCurEffect();
    void setEffect(int num);
    int getCurEffectNum();
    void nextEffect();
    void prevEffect();
    void reloadCurEff();
};

#endif // EFFECTSLIST_H
