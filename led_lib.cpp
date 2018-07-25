#include "led_lib.h"

//основной массив со значениями цветов светодиодов
//Каждый тик его содержимое рисует на led матрице при помощи функции led_show()
static Color led_mas[HOR_LED_CNT][VER_LED_CNT];
static QList<QPushButton*> leds;

//показывать текстовую информацию поверх ячеек стола?
static bool debug_text = true;

//------------------------- COMMON function -------------------------------
void set_debug_text_flag(bool flag)
{
    debug_text = flag;
}

void init_leds(QList<QPushButton*> buttons)
{
    leds = buttons;
}

static void setPixColor(byte x, byte y, byte r, byte g, byte b)
{
    QPushButton *but = leds[(9 - x) * 10 + y];
    but->setAutoFillBackground(true);
    but->setStyleSheet(QString("background-color: %1;  color: %2").arg((new QColor(r, g, b))->name(), (new QColor((r + 128) % 256, (g + 128) % 256, (b + 128) % 256))->name()));
    if (debug_text) {
        but->setText(QString("%1\n%2\n%3").arg(QString::number(r), QString::number(g), QString::number(b)));
    } else {
        but->setText("");
    }


}

//------------------------- NOT DEBUB libs functions -------------------------------

void color_set(COLOR_TYPE *dest, COLOR_TYPE src)
{
#ifdef DEBUG
    if (src > MAX_LED_VAL || src < 0) {
        out("Error led_color_set: src val: %ld\n", src);
    }
#endif

    *dest = src;
}

void color_add(COLOR_TYPE *dest, COLOR_TYPE src)
{
#ifdef DEBUG
  if (src > MAX_LED_VAL || src < 0) {
    out("Error led_color_add: src val: %ld\n", src);
  }
#endif

  if ((long) *dest + src > MAX_LED_VAL) {
    *dest = MAX_LED_VAL;
  } else {
    *dest += src;
  }
}

void color_sub(COLOR_TYPE *dest, COLOR_TYPE src)
{
#ifdef DEBUG
    if (src > MAX_LED_VAL || src < 0) {
        out("Error led_color_sub: src val: %ld\n", src);
    }
#endif

    if ((long) *dest - src < 0) {
        *dest = 0;
    } else {
        *dest -= src;
    }
}

Color color_create(COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b)
{
#ifdef DEBUG
    if (r > MAX_LED_VAL || r < 0) {
        out("Error color_create: red color is out of range 0..%d\n", MAX_LED_VAL);
    }
        if (g > MAX_LED_VAL || g < 0) {
        out("Error color_create: green color is out of range 0..%d\n", MAX_LED_VAL);
    }
    if (b > MAX_LED_VAL || b < 0) {
        out("Error color_create: blue color is out of range 0..%d\n", MAX_LED_VAL);
    }
#endif

    Color ret_color =  {
        .r = r,
        .g = g,
        .b = b,
    };
    return ret_color;
}

//------------------------- COMMON lib functions -------------------------------

static void color_oper(Color *dest, Color src, OPER_FUNC(oper))
{
    if (dest != NULL) {
        oper(&(dest->r), src.r);
        oper(&(dest->g), src.g);
        oper(&(dest->b), src.b);
    } else {
        out("Error in function color_oper: dest == NULL\n");
    }
}

Color *led_get(byte x, byte y)
{
    if(x < VER_LED_CNT && x >= 0 && y < HOR_LED_CNT && y >= 0) {
        return &led_mas[x][y];
    } else {
        out("Error in function led_get: return_val == NULL x:%d y:%d\n", x, y);
        return NULL;
    }
}

void led_set(byte x, byte y, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper))
{
    led_set(x, y, color_create(r, g, b), oper);
}

void led_set(byte x, byte y, Color src, OPER_FUNC(oper))
{
    led_set(led_get(x, y), src, oper);
}

void led_set(Color *dst, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper))
{
    color_oper(dst, color_create(r, g, b), oper);
}

void led_set(Color *dst, Color src, OPER_FUNC(oper))
{
    color_oper(dst, src, oper);
}

void led_fill_color(COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper))
{
    led_fill_color(color_create(r, g, b), oper);
}

void led_fill_color(Color cl, OPER_FUNC(oper))
{
    byte i, j;
    for (i = 0; i < VER_LED_CNT; i++) {
        for (j = 0; j < HOR_LED_CNT; j++) {
            led_set(i, j, cl, oper);
        }
    }
}

void led_draw_line(byte x1, byte y1, byte x2, byte y2, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper))
{
    led_draw_line(x1, y1, x2, y2, color_create(r, g, b), oper);
}

void led_draw_line(byte x1, byte y1, byte x2, byte y2, Color color, OPER_FUNC(oper))
{
#ifdef DEBUG
    if (x1 >= VER_LED_CNT || x2 >= VER_LED_CNT || y1 >= HOR_LED_CNT || y2 >= HOR_LED_CNT || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
        out("Error in function led_draw_line: coord is out of range:  x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);
        return;
    }
#endif
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    byte signX = x1 < x2 ? 1 : -1;
    byte signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;
    int error2;

    led_set(x2, y2, color, oper);
    while (x1 != x2 || y1 != y2) {
        led_set(x1, y1, color, oper);
        error2 = error * 2;

        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void led_drow_rectangle(byte x1, byte y1, byte x2, byte y2, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper))
{
    led_drow_rectangle(x1, y1, x2, y2, color_create(r, g, b), oper);
}

void led_drow_rectangle(byte x1, byte y1, byte x2, byte y2, Color border_color, OPER_FUNC(oper))
{
#ifdef DEBUG
    if (x1 >= VER_LED_CNT || x2 >= VER_LED_CNT || y1 >= HOR_LED_CNT || y2 >= HOR_LED_CNT || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
        out("Error in function led_drow_rectangle: coord is out of range:  x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);
        return;
    }
#endif
        led_draw_line(x1, y1, x1, y2, border_color, oper);
    if (x1 != x2) {
        led_draw_line(x2, y1, x2, y2, border_color, oper);
    }
    if (x2 - x1 > 1) {
        led_draw_line(x1 + 1, y1, x2 - 1, y1, border_color, oper);
        led_draw_line(x1 + 1, y2, x2 - 1, y2, border_color, oper);
    } else if (x1 - x2 > 1) {
        led_draw_line(x1 - 1, y1, x2 + 1, y1, border_color, oper);
        led_draw_line(x1 - 1, y2, x2 + 1, y2, border_color, oper);
    }
}

void led_drow_rectangle(byte x1, byte y1, byte x2, byte y2, Color border_color, Color fill_color, OPER_FUNC(oper))
{
    if (x1 > x2) {
        x1 ^= x2 ^= x1 ^= x2; //swap x1 <-> x2
    }
    if (y1 > y2) {
        y1 ^= y2 ^= y1 ^= y2; //swap x1 <-> x2
    }
    if (x2 - x1 > 1 && y2 - y1  > 1){
        led_drow_filled_rectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, fill_color, oper);
    }
    led_drow_rectangle(x1, y1, x2, y2, border_color, oper);
}

void led_drow_filled_rectangle(byte x1, byte y1, byte x2, byte y2, COLOR_TYPE r, COLOR_TYPE g, COLOR_TYPE b, OPER_FUNC(oper)) {
    led_drow_filled_rectangle(x1, y1, x2, y2, color_create(r, g, b), oper);
}

void led_drow_filled_rectangle(byte x1, byte y1, byte x2, byte y2, Color fill_color, OPER_FUNC(oper))
{
#ifdef DEBUG
    if (x1 >= VER_LED_CNT || x2 >= VER_LED_CNT || y1 >= HOR_LED_CNT || y2 >= HOR_LED_CNT || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
        out("Error in function led_drow_filled_rectangle: coord is out of range:  x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);
        return;
    }
#endif
    if (x1 > x2) {
        x1 ^= x2 ^= x1 ^= x2;
    }
    if (y1 > y2) {
        y1 ^= y2 ^= y1 ^= y2;
    }
    byte i, j;

    for (i = x1; i <= x2; ++i) {
        for (j = y1; j <= y2; ++j) {
            led_set(i, j, fill_color, oper);
        }
    }
}

void led_show()
{
  byte i, j;
  Color cl;
  for (i = 0; i < HOR_LED_CNT; ++i) {
    for (j = 0; j < VER_LED_CNT; ++j) {
      if (DIR == 0) {
        cl = *led_get(i, j);
      } else if (DIR == 1) {
        cl = *led_get(j, 9 - i);
      } else if (DIR == 2) {
        cl = *led_get(9 - i, 9 - j);
      } else if (DIR == 3) {
        cl = *led_get(9 - j, i);
      }
      setPixColor(i, j, cl.r, cl.g, cl.b);
    }
  }
}

void led_clear()
{
  led_fill_color(0, 0, 0, SET);
}
