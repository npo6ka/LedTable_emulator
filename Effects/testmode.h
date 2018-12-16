#pragma once

#include "Effects/effect.h"

class TestMode : public Effect
{
    struct Box {
        uint16_t height, width;
        uint16_t xPos, yPos;
        uint8_t hue;
        uint8_t speed;
    };

    uint16_t hiWidth = 256 * WIDTH;
    uint16_t hiHeight = 256 * HEIGHT;

public:
    TestMode() {}

    void on_init() {

    }

    void on_tick() {

        Box box;

        box.height = 1;
        box.width = 3 * 256;
        box.xPos = 0;
        box.yPos = 5;
        box.speed = 16;

        hi(box);
    }

    void hi(Box b) {
        int y = b.yPos;
        for (uint16_t x = b.xPos; x < hiWidth; x+= b.speed) {

            FastLED.clear();

            for (int boxwidth = 0; boxwidth <= b.width; boxwidth++) {
                uint16_t actualPixel = (x + boxwidth) >> 8;
                uint16_t actualBrightness = (x + boxwidth) & 0xFF;
                renderIfVisible(actualPixel, 0, CHSV(b.hue, 255, 255 - actualBrightness));
            }

            LEDS.show();
        }
    }

    //                renderIfVisible((x >> 8), y, CHSV(b.hue, 255, 255 - x & 0xFF));
    //                renderIfVisible((x + b.width) >> 8, y, CHSV(b.hue, 255, x & 0xFF));

    void renderIfVisible(uint16_t x, uint16_t y, CHSV chsv) {
        getPix(x, y) += chsv;
    }
};
