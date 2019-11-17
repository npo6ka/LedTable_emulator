#pragma once

#include "Effects/effect.h"

#define ACCURACY 100
#define MIN_VEC_SIZE 5
#define MAX_VEC_SIZE 10
#define RAINBOW_TICK_SIZE 4 //кол-во тиков до инкремента тика радуги

class TestMode : public Effect
{
    int32_t x;
    int32_t y;
    int32_t vec_x;
    int32_t vec_y;
    int tick;

    uint16_t XY( uint8_t x, uint8_t y)
    {
        return y * WIDTH + x;
    }
public:
    TestMode() {}

    void on_init() {

    }

    void on_update(void) {
        float speed = 1;

        // get some 2 random moving points
        uint8_t x2 = 1;//inoise8(millis() * speed, 25355, 685 ) / 16;
        uint8_t y2 = 1;//inoise8(millis() * speed, 355, 11685 ) / 16;

        uint8_t x3 = 1;//inoise8(millis() * speed, 55355, 6685 ) / 16;
        uint8_t y3 = 1;//inoise8(millis() * speed, 25355, 22685 ) / 16;

        // and one Lissajou function
        uint8_t x1 = beatsin8(23 * speed, 0, 15);
        uint8_t y1 = beatsin8(28 * speed, 0, 15);

        for (uint8_t y = 0; y < HEIGHT; y++) {
          for (uint8_t x = 0; x < WIDTH; x++) {

            // calculate distances of the 3 points from actual pixel
            // and add them together with weightening
            uint8_t  dx =  abs(x - x1);
            uint8_t  dy =  abs(y - y1);
            uint8_t dist = 2 * sqrt((dx * dx) + (dy * dy));

            dx =  abs(x - x2);
            dy =  abs(y - y2);
            dist += sqrt((dx * dx) + (dy * dy));

            dx =  abs(x - x3);
            dy =  abs(y - y3);
            dist += sqrt((dx * dx) + (dy * dy));

            // inverse result
            uint8_t color = 1000 / dist;

            // map color between thresholds
            if (color > 0 and color < 60) {
              setPixColor(x, y, CHSV(color * 9, 255, 255));
            } else {
              setPixColor(x, y, CHSV(0, 255, 255));
            }
              // show the 3 points, too
              setPixColor(x, y, CRGB(255, 255,255));
              setPixColor(x, y, CRGB(255, 255,255));
              setPixColor(x, y, CRGB(255, 255,255));
            }
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
