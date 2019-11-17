#pragma once

#include "Effects/effect.h"

#define ACCURACY 100
#define RAINBOW_TICK_SIZE 4

typedef struct Point
{
    int32_t x;
    int32_t y;
    uint8_t hue;
    uint32_t pr; //point_radius
    uint32_t br; //bright_radius
} Point;

class TestMode : public Effect
{
    uint8_t tick;
    Point p1;
    uint32_t rot;
    uint32_t v;

private:
    static float get_func_brithtness(uint32_t distance, Point pnt)
    {
        if (distance <= pnt.pr) {
            return 1;
        } else if (distance >= pnt.pr + pnt.br) {
            return 0;
        } else {
            float val = (float)(distance - pnt.pr) / pnt.br;
            return ( 7.3890560 /* e^2 */ ) / (50 * val + 7) - 0.13;
        }
    }

    static void render_point(Point pnt)
    {
      int i, j;
      for (i = 0; i < WIDTH; ++i) {
        for(j = 0; j < HEIGHT; ++j) {
          int loc_x = i * ACCURACY + ACCURACY / 2;
          int loc_y = j * ACCURACY + ACCURACY / 2;

          uint32_t distance = sqrt((loc_x - pnt.x) * (loc_x - pnt.x) + (loc_y - pnt.y) * (loc_y - pnt.y));

          float bright = get_func_brithtness(distance, pnt) * 0.2;
          CRGB clr = getPix(i, j);
          CRGB pnt_clr = CHSV(pnt.hue, 255, 255);
          clr.r = qadd8(clr.r, (float)pnt_clr.r * bright);
          clr.g = qadd8(clr.g, (float)pnt_clr.g * bright);
          clr.b = qadd8(clr.b, (float)pnt_clr.b * bright);
          setPixColor(i, j, clr);
        }
      }
    }

public:
    TestMode() {}

    void on_init() {
        tick = 0;
        rot = 0;
        v = 1;

        p1.x = 550;
        p1.y = 550;
        p1.hue = 0;
        p1.pr = 400;
        p1.br = 200;
    }

    //tick 0-255
    float get_pi_tick(uint8_t tick) {
        return 3.141592/* pi */ * 2 * tick / 255;
    }

    void on_tick(void) {
        float angle = get_pi_tick(tick);
        float radius = 0.9;
        p1.x = ACCURACY * WIDTH * (radius * cos(angle) + 1) / 2;
        p1.y = ACCURACY * HEIGHT * (radius * sin(angle) + 1) / 2;
        p1.hue++;

        // FastLED.clear();
        fader(5);
        render_point(p1);
        tick = tick + 3;
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
