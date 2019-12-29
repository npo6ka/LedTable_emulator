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

    void on_update(void) {
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



/*#pragma once

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
        uint8_t x2 = inoise8(millis() * speed, 25355, 685 ) / 16;
        uint8_t y2 = inoise8(millis() * speed, 355, 11685 ) / 16;

        uint8_t x3 = inoise8(millis() * speed, 55355, 6685 ) / 16;
        uint8_t y3 = inoise8(millis() * speed, 25355, 22685 ) / 16;

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
