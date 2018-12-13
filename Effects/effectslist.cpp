#include "effectslist.h"

#include "00_slow_random.h"
#include "01_simple_rainbow.h"
#include "02_dribs.h"
#include "03_rain.h"
#include "04_all_random.h"

#include "testmode.h"


void EffectsList::setEffAmnt() {
    int cnt = 0;
    Effect *eff = getEffect(cnt);

    while(eff != NULL) {
        free(eff);
        cnt++;
        eff = getEffect(cnt);
    }
    amnt = cnt;
}

EffectsList::EffectsList() {
    setEffAmnt();
    if (amnt > 0) {
        setEffect(0);
    } else {
        setErrorEffect();
    }
}

Effect *EffectsList::getEffect(int num) {
    switch (num) {
    case 0:
        return new TestMode();
    case 1:
        return new SlowRandom();
    case 2:
        return new SimpleRainbow();
    case 3:
        return new Dribs();
    case 4:
        return new Rain();
    case 5:
        return new AllRandom();
    /*case 6:
        return new Rain();
    case 7:
        return new Rain();
    case 8:
        return new Rain();
    case 9:
        return new Rain();
    case 10:
        return new Rain();
    case 11:
        return new Rain();
    case 12:
        return new Rain();
    case 13:
        return new Rain();
    case 14:
        return new Rain();*/
    default:
        return NULL;
    }
}

void EffectsList::setErrorEffect() {
    if (curEffect) free(curEffect);
    curEffect = new ErrorEffect();
}

Effect *EffectsList::getCurEffect() {
    return curEffect;
}

void EffectsList::setEffect(int num) {
    free(curEffect);
    FastLED.clear();

    curEffect = getEffect(num);

    if (curEffect == NULL) {
        setErrorEffect();
        return;
    }

    curEffect->on_init();
    curNum = num;
}

int EffectsList::getCurEffectNum() {
    return curNum;
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

void EffectsList::reloadCurEff() {
    setEffect(curNum);
}
