#include "showmatrix.h"

//основной массив со значениями цветов светодиодов
//Каждый тик его содержимое рисует на led матрице при помощи функции led_show()
static QList<QPushButton*> ledButtons;

//показывать текстовую информацию поверх ячеек стола
static bool debug_text = true;

void set_debug_text_flag(bool flag)
{
    debug_text = flag;
}

void init_leds(QList<QPushButton*> buttons)
{
    ledButtons = buttons;
}

void setPixColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b)
{
    QPushButton *but = ledButtons[num];
    but->setAutoFillBackground(true);
    but->setStyleSheet(QString("background-color: %1;  color: %2").arg((new QColor(r, g, b))->name(), (new QColor((r + 128) % 256, (g + 128) % 256, (b + 128) % 256))->name()));

    /*CHSV val = rgb2hsv_approximate(CRGB(r, g, b));
    CRGB text_cl = CHSV(val.h + 128, val.s, val.v);
    but->setStyleSheet(QString("background-color: %1;  color: %2").arg((new QColor(r, g, b))->name(), (new QColor(text_cl.r, text_cl.g, text_cl.b))->name()));*/

    if (debug_text) {
        but->setText(QString("%1\n%2\n%3").arg(QString::number(r), QString::number(g), QString::number(b)));
    } else {
        but->setText("");
    }
}
