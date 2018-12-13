#pragma once

#include "Effects/effect.h"

class TestMode : public Effect
{
    uint8_t step = 2;

public:
    TestMode() {}

    void on_init() {

    }

    void on_tick() {
        int i;

        for (i = 0; i < LEDS_CNT; i++) {
            getPix(i / 10, i % 10) = CRGB(random8(255), random8(255), random8(255));
        }
    }
};


/*
#define lenght 3
#define radius HOR_LED_CNT / 2
#define tick sup_val[0]

void animation_04()
{
  int i;
  byte cur_ring;
  int step = 255 / lenght;
  led_clear();

  for (i = lenght - 1; i >= 0; --i) {
      cur_ring = (byte)(tick - i) % 10;
      led_drow_rectangle(0 + cur_ring, 0 + cur_ring, HOR_LED_CNT - cur_ring - 1, VER_LED_CNT - cur_ring - 1, 0, 0, 255 - step * i, SET);
  }

  tick = (tick + 1) % 100;
  delay(150);
}

#undef lenght
#undef radius
#undef tick

*/
