#include "effectslist.h"

#include "00_slow_random.h"
#include "01_simple_rainbow.h"

#include "testmode.h"

#define MAX_EFFECTS 50

EffectsList::EffectsList() {
    init();
}

void EffectsList::init() {
    curEffect = NULL;
    amnt = MAX_EFFECTS;
    Effect *eff = NULL;

    while(eff == NULL && amnt >= 0) {
        amnt--;
        eff = getNewEffectInstance(amnt);
    }

    if (eff == NULL) {
        setErrorEffect();
    } else {
        curNum = amnt;
        setEffect(eff);
        amnt += 1;
    }
    setEffect(2);
}

Effect *EffectsList::getNewEffectInstance(int num) {
    switch (num) {
    case 0:
        return new SlowRandom();
    case 1:
        return new SimpleRainbow();
    case 2:
        return new TestMode();
    default:
        return NULL;
    }
}

void EffectsList::setErrorEffect() {
    clearCurEffect();
    curEffect = new ErrorEffect();
}

Effect *EffectsList::getCurEffect() {
    return curEffect;
}

int EffectsList::getCurEffectNum() {
    return curNum;
}

void EffectsList::clearCurEffect() {
    if (getCurEffect()) {
        delete curEffect;
        curEffect = NULL;
    }
}

void EffectsList::setEffect(int num) {
    setEffect(getNewEffectInstance(num));
    curNum = num;
}

void EffectsList::setEffect(Effect *eff) {
    clearCurEffect();

    curEffect = eff;
    if (curEffect == NULL) {
        setErrorEffect();
        curNum = -1;
        return;
    }

    curEffect->on_clear();
    curEffect->on_init();
}

void EffectsList::nextEffect() {
    if (curNum + 1 >= amnt) {
        setEffect(0);
    } else {
        setEffect(curNum + 1);
    }
}

void EffectsList::prevEffect() {
    if (curNum - 1 < 0) {
        setEffect(amnt - 1);
    } else {
        setEffect(curNum - 1);
    }
}

//перезапустить текущий эффект
void EffectsList::reloadCurEff() {
    setEffect(curNum);
}
