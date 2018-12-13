#define FASTLED_INTERNAL
#include "fastled.h"

#define NULL nullptr

void *pSmartMatrix = NULL;

CFastLED FastLED;

static CLEDController cont;
CLEDController *CLEDController::m_pHead = NULL;
CLEDController *CLEDController::m_pTail = NULL;
static uint32_t lastshow = 0;

uint32_t _frame_cnt=0;
uint32_t _retry_cnt=0;


CFastLED::CFastLED()
{
    // clear out the array of led controllers
    m_Scale = 255;
    m_nFPS = 0;
    m_pPowerFunc = NULL;
    m_nPowerData = 0xFFFFFFFF;
}

CLEDController &CFastLED::addLeds(struct CRGB *data, int nLedsOrOffset, int nLedsIfOffset)
{
    int nOffset = (nLedsIfOffset > 0) ? nLedsOrOffset : 0;
    int nLeds = (nLedsIfOffset > 0) ? nLedsIfOffset : nLedsOrOffset;

    cont.init();
    cont.setLeds(data + nOffset, nLeds);
    FastLED.setMaxRefreshRate(cont.getMaxRefreshRate(), true);
    return cont;
}

void CFastLED::show(uint8_t scale) {
    // guard against showing too rapidly
    while(m_nMinMicros && ((micros()-lastshow) < m_nMinMicros));
    lastshow = micros();

    // If we have a function for computing power, use it!
    if(m_pPowerFunc) {
        scale = (*m_pPowerFunc)(scale, m_nPowerData);
    }

    CLEDController *pCur = CLEDController::head();
    while(pCur) {
        uint8_t d = pCur->getDither();
        if(m_nFPS < 100) { pCur->setDither(0); }
        pCur->showLeds(scale);
        pCur->setDither(d);
        pCur = pCur->next();
    }
    countFPS();
}

int CFastLED::count() {
    int x = 0;
    CLEDController *pCur = CLEDController::head();
    while( pCur) {
        x++;
        pCur = pCur->next();
    }
    return x;
}

CLEDController & CFastLED::operator[](int x) {
    CLEDController *pCur = CLEDController::head();
    while(x-- && pCur) {
        pCur = pCur->next();
    }
    if(pCur == NULL) {
        return *(CLEDController::head());
    } else {
        return *pCur;
    }
}

void CFastLED::showColor(const struct CRGB & color, uint8_t scale) {
    while (m_nMinMicros && ((micros() - lastshow) < m_nMinMicros));
    lastshow = micros();

    // If we have a function for computing power, use it!
    if (m_pPowerFunc) {
        scale = (*m_pPowerFunc)(scale, m_nPowerData);
    }

    CLEDController *pCur = CLEDController::head();
    while (pCur) {
        uint8_t d = pCur->getDither();
        if (m_nFPS < 100) { pCur->setDither(0); }
        pCur->showColor(color, scale);
        pCur->setDither(d);
        pCur = pCur->next();
    }
    countFPS();
}

void CFastLED::clear(bool writeData) {
    if (writeData) {
        showColor(CRGB(0,0,0), 0);
    }
    clearData();
}

void CFastLED::clearData() {
    CLEDController *pCur = CLEDController::head();
    while (pCur) {
        pCur->clearLedData();
        pCur = pCur->next();
    }
}

void CFastLED::delay(unsigned long ms) {
    unsigned long start = millis();
    do {
        show();
    } while((millis() - start) < ms);
}

void CFastLED::setTemperature(const struct CRGB & temp) {
    CLEDController *pCur = CLEDController::head();
    while(pCur) {
        pCur->setTemperature(temp);
        pCur = pCur->next();
    }
}

void CFastLED::setCorrection(const struct CRGB & correction) {
    CLEDController *pCur = CLEDController::head();
    while(pCur) {
        pCur->setCorrection(correction);
        pCur = pCur->next();
    }
}

void CFastLED::setDither(uint8_t ditherMode)  {
    CLEDController *pCur = CLEDController::head();
    while(pCur) {
        pCur->setDither(ditherMode);
        pCur = pCur->next();
    }
}

extern int noise_min;
extern int noise_max;

void CFastLED::countFPS(int nFrames) {
  static int br = 0;
  static uint32_t lastframe = 0; // millis();

  if (br++ >= nFrames) {
        uint32_t now = millis();
        now -= lastframe;
        m_nFPS = (br * 1000) / now;
    br = 0;
    lastframe = millis();
  }
}

void CFastLED::setMaxRefreshRate(uint16_t refresh, bool constrain) {
  if (constrain) {
    // if we're constraining, the new value of m_nMinMicros _must_ be higher than previously (because we're only
    // allowed to slow things down if constraining)
    if (refresh > 0) {
      m_nMinMicros = ( (1000000/refresh) >  m_nMinMicros) ? (1000000/refresh) : m_nMinMicros;
    }
  } else if (refresh > 0) {
    m_nMinMicros = 1000000 / refresh;
  } else {
    m_nMinMicros = 0;
  }
}
