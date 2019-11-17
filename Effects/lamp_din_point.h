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

private:
    //arg2: horizontal barrier = true or vertical = false
    void rainbow_point_gen_vector(bool horVer) {
        int16_t dir = horVer ? 1 : -1;

        vec_x = (vec_x > 0 ? -dir : dir) * random(MIN_VEC_SIZE, MAX_VEC_SIZE);
        vec_y = (vec_y > 0 ? dir : -dir) * random(MIN_VEC_SIZE, MAX_VEC_SIZE);

        if (vec_y == 0 && vec_x == 0) {
            rainbow_point_gen_vector(horVer);
        }
    }

    void rainbow_point_move_point() {
        x += vec_x;
        y += vec_y;

        if (x < 0) {
            x += ACCURACY * WIDTH - 1;
            //rainbow_point_gen_vector(true);
        } else if (x >= ACCURACY * WIDTH) {
            x -= ACCURACY * WIDTH + 1;
            //rainbow_point_gen_vector(true);
        }

        if (y < 0) {
            y = 0;
            rainbow_point_gen_vector(false);
        } else if (y >= ACCURACY * HEIGHT) {
            y = ACCURACY * HEIGHT - 1;
            rainbow_point_gen_vector(false);
        }
    }

    int32_t point_distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    void rainbow_point_render_point() {
        int i, j;

        for (i = 0; i < WIDTH; ++i) {
            for(j = 0; j < HEIGHT; ++j) {
                int32_t loc_x = i * ACCURACY + ACCURACY / 2;
                int32_t loc_y = j * ACCURACY + ACCURACY / 2;

                int32_t dis1 = point_distance(x, y, loc_x, loc_y);
                int32_t dis2 = point_distance(x, y, loc_x - WIDTH * ACCURACY, loc_y);
                int32_t dis3 = point_distance(x, y, loc_x + WIDTH * ACCURACY, loc_y);

                dis1 = dis1 < dis2 ? dis1 : dis2;
                dis1 = dis1 < dis3 ? dis1 : dis3;

                float chsv = (dis1 / 8 + tick / RAINBOW_TICK_SIZE) % MAX_HSV;

                setPixColor(i, j, CHSV(chsv, 255, 255));
            }
        }
    }
public:
    TestMode() {}

    void on_init() {
        tick = 0;
        x = random16(0, (WIDTH - 1) * ACCURACY);
        y = random16(0, (HEIGHT - 1) * ACCURACY);

        vec_x = (int32_t)random(0, MAX_VEC_SIZE * 2) - MAX_VEC_SIZE;
        vec_y = (int32_t)random(0, MAX_VEC_SIZE * 2) - MAX_VEC_SIZE;
    }

    //tick 0-255
    float get_pi_tick(uint8_t tick) {
        return 3.141592/* pi */ * 2 * tick / 255;
    }

    void on_tick(void) {
        FastLED.clear();

        int i;

        tick = (tick + 1) % ((MAX_HSV + 1) * RAINBOW_TICK_SIZE);

        rainbow_point_move_point();
        rainbow_point_render_point();
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
