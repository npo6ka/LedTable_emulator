#ifndef LED_LIB_H
#define LED_LIB_H

#include <QPushButton>
#include "debug.h"

#define byte int

#define HOR_LED_CNT 10 // горизонтальное количество светодиодов
#define VER_LED_CNT 10 // вертикальное количество светодиодов
#define LED_CNT HOR_LED_CNT * VER_LED_CNT // общее количество светодиодов
#define MAX_LED_VAL 255 //максимальная яркость

//Вспомогательные глобальные переменные для режимов и игр
#define SUP_VAL_CNT 10 //размер массива вспомогательных переменных
//byte sup_mas[HOR_LED_CNT][VER_LED_CNT];
//int sup_val[SUP_VAL_CNT];

//возможные операции со светодиодами (параметр "OPER_FUNC(oper)" заменяется на ADD, SUB или SET)
#define ADD color_add
#define SUB color_sub
#define SET color_set
#define OPER_FUNC(NAME) void (*NAME)(COLOR_TYPE *, COLOR_TYPE)

#ifdef DEBUG
    #define COLOR_TYPE long
#else
    #define COLOR_TYPE byte
#endif

typedef struct Color {
  COLOR_TYPE r;
  COLOR_TYPE g;
  COLOR_TYPE b;
} Color;

//поворот изображения на матрице
#define DIR 1

void set_debug_text_flag(bool flag);
void init_leds(QList<QPushButton*> buttons);

Color color_create(COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b);
Color *led_get(byte x, byte y);
void led_set(byte x, byte y, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper));
void led_set(byte x, byte y, Color src, OPER_FUNC(oper));
void led_set(Color *dst, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper));
void led_set(Color *dst, Color src, OPER_FUNC(oper));
void led_fill_color(COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper));
void led_fill_color(Color cl, OPER_FUNC(oper));
void led_draw_line(byte x1, byte y1, byte x2, byte y2, Color color, OPER_FUNC(oper));
void led_draw_line(byte x1, byte y1, byte x2, byte y2, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper));
void led_drow_rectangle(byte x1, byte y1, byte x2, byte y2, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper));
void led_drow_rectangle(byte x1, byte y1, byte x2, byte y2, Color border_color, OPER_FUNC(oper));
void led_drow_rectangle(byte x1, byte y1, byte x2, byte y2, Color border_color, Color fill_color, OPER_FUNC(oper));
void led_drow_filled_rectangle(byte x1, byte y1, byte x2, byte y2, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper));
void led_drow_filled_rectangle(byte x1, byte y1, byte x2, byte y2, Color fill_color, OPER_FUNC(oper));
void led_show();
void led_clear();
#endif // LED_LIB_H
