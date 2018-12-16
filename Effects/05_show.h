#pragma once

#include "Effects/effect.h"

class Snow : public Effect
{
    uint8_t step = 2;
    int density = 10;

public:
    Snow() {}

    void on_init() {

    }

    void on_tick() {
        // сдвигаем всё вниз
        for (uint8_t x = 0; x < WIDTH; x++) {
            for (uint8_t y = 0; y < HEIGHT - 1; y++) {
                setPixColor(x, y, getPixColor(x, y + 1));
            }
        }

        for (uint8_t x = 0; x < WIDTH; x++) {
            // заполняем случайно верхнюю строку
            // а также не даём двум блокам по вертикали вместе быть
            if (getPixColor(x, HEIGHT - 2) == 0 && (random8(density) == 0)) {
                setPixColor(x, HEIGHT - 1, 0xE0FFFF - 0x101010 * random8(4));
            } else {
                setPixColor(x, HEIGHT - 1, 0x000000);
            }
        }
    }
};
