#pragma once

#include "Effects/effect.h"


class TestMode : public Effect
{
    uint8_t x;
    uint8_t y;
    bool dir;
    uint8_t hue;
    uint8_t step;
    uint8_t tick;

public:
    TestMode() {}

    void on_init() {
        x = 0;
        y = 0;
        step = 2;
        dir = true;
        hue = random8();
        tick = 0;
    }

    void on_tick(void) {
        setPixColor(x, y, CHSV(hue, 255, 255));

        tick++;
        if (tick >= step) {
            tick = 0;
            hue++;
        }

        if (dir) {
            if (x + 1 >= HEIGHT) {
                y++;
                dir = !dir;
            } else {
                x++;
            }
        } else {
            if (x - 1 < 0) {
                y++;
                dir = !dir;
            } else {
                x--;
            }
        }

        if (y >= WIDTH) {
            y = 0;
        }
    }
};




// снег
/*
 *     uint8_t step; //среднее кол-во тиков до сдвига снежинки
    uint8_t range = 3; //максимальное отклонение от шага
    int density; //вероятность генерации новой снежинки
    uint8_t mas[WIDTH][HEIGHT];

public:
    TestMode() {}

    void on_init() {
        step = 10;
        range = 3;
        density = 100;
        memset(mas, 0, WIDTH * HEIGHT);
    }

    void on_tick(void) {

        // сдвигаем вниз
        for (int8_t y = HEIGHT - 1; y >= 0; y--) {
            for (uint8_t x = 0; x < WIDTH; x++) {
                if (mas[x][y] && !random(0, step)) {
                    if (y < HEIGHT - 1) {
                        if (mas[x][y] == 1 && x + 1 < WIDTH) {
                            mas[x + 1][y + 1] = 2;
                            setPixColor(x + 1, y + 1, getPixColor(x, y));
                        } else if (x - 1 >= 0) {
                            mas[x - 1][y + 1] = 1;
                            setPixColor(x - 1, y + 1, getPixColor(x, y));
                        }
                    }
                    mas[x][y] = 0;
                    setPixColor(x, y, 0);
                }
            }
        }

        for (uint8_t x = 0; x < WIDTH - 1; x++) {
            // заполняем случайно верхнюю строку
            // а также не даём двум блокам по вертикали вместе быть
            if (random(0, density) == 0) {
                setPixColor(x, 0, 0xE0FFFF - 0x101010 * random(0, 4));
                mas[x][0] = random(1, 2);
            }
        }

    }
*/
