#pragma once

#include <QList>
#include <QPushButton>

void set_debug_text_flag(bool flag);
void init_leds(QList<QPushButton*> buttons);
void draw_pixel(uint8_t num, uint8_t r, uint8_t g, uint8_t b);
