#ifndef ANIMATION02_H
#define ANIMATION02_H

#include "mode.h"
#include <math.h>
#include "FastLED/fastled.h"

/*MAX_LED_VAL
HOR_LED_CNT
VER_LED_CNT*/


class Animation02: public Mode
{
public:
    Animation02() : Mode()  {}
    ~Animation02() {}

    int accuracy = 10;
    float point_size = 1.0;
    float point_radius = 20;
    int x = random(0, (HOR_LED_CNT - 1) * accuracy), y = random(0, (VER_LED_CNT - 1) * accuracy);
    int vec_x = random(-accuracy, accuracy), vec_y = random(-accuracy, accuracy);
    int tick = 0;

    void on_init(void) {

    }

    void on_tick(void) {
        tick++;
        move_point();
        render_point(x, y);
    }

    void move_point() {
        x += vec_x;
        y += vec_y;

        FastLED.show();

        bool is_touch = false;
        if (x > HOR_LED_CNT * accuracy) {
            x = HOR_LED_CNT * accuracy;
            is_touch = true;
        } else if (x < 0) {
            x = 0;
            is_touch = true;
        } if (y > VER_LED_CNT * accuracy) {
            y = VER_LED_CNT * accuracy;
            is_touch = true;
        } else if (y < 0) {
            y = 0;
            is_touch = true;
        }

        if (is_touch) {
            vec_x = (random(0, 1) * 2) - 1;
            vec_y = (random(0, 1) * 2) - 1;
        }
    }

    void render_point(int x, int y) {
        int i, j;
        for (i = 0; i < HOR_LED_CNT; ++i) {
            for(j = 0; j < VER_LED_CNT; ++j) {
                int loc_x = (i + 0.5) * accuracy;
                int loc_y = (j + 0.5) * accuracy;

                int distance = sqrt((loc_x - x) * (loc_x - x) + (loc_y - y) * (loc_y - y));

                float bright = get_func_brithtness(distance);
                Color clr = rainbow_make_color(tick % 360, 100, 40);

                led_set(i, j, (float)clr.r * bright, (float)clr.g * bright, (float)clr.b * bright, SET);
            }
        }
    }

    float get_func_brithtness(int distance) {
        if (distance < accuracy * point_size) {
            return 1;
        } else {
            float ret_val = 255 + accuracy * point_size - distance * point_radius;

            if (ret_val < 0) {
                ret_val = 0;
            }
            return ret_val / 255;
        }
    }
};

#endif // ANIMATION02_H
