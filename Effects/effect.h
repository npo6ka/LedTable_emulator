#ifndef EFFECT_H
#define EFFECT_H

#include "QTime"
#include "matrixlib.h"

class Effect
{
public:
    Effect() { }
    /* Инициализация режима, установка начальный значений.
    *  Выполняется единожды, при выборе нового режима.
    * */
    virtual void on_init() {}

    /* on_update обязательно нужно описать в наследукмом классе.
    *  Обновление логики эффекта.
    *  Часть цикла работы режима.
    * */
    virtual void on_update() = 0;

    /* on_render может быть переинициализирован в наследукмом классе.
    *  Обновление графики эффекта.
    *  Часть цикла работы режима.
    * */
    virtual void on_render() {
        FastLED.show();
    }

    /* on_clear может быть переинициализирован в наследукмом классе.
     * Выполняется единожды, при выборе нового режима, перед вызовом on_init.
    *  Действия с состоянием матрицы оставшейся после предыдущего режима.
    *  По умолчанию всё стрирается.
    * */
    virtual void on_clear() {
        FastLED.clear();
    }
};

#endif // EFFECT_H


/*#ifndef EFFECT_H
#define EFFECT_H

#include "QTime"
#include "matrixlib.h"

typedef void(*eff_func_prepare)();
typedef void(*eff_func_render)();
typedef void(*eff_func_update)(unsigned long);

struct eff_instance
{
    unsigned char name[11];
    eff_func_prepare prepare;
    eff_func_render render;
    eff_func_update update;
    uint16_t data_size;
    void** data;
};

void game_set_ups(int ups);
void game_setup();

//void game_save(const void *buf, uint16_t size);
//void game_load(void *buf, uint16_t size);

#endif // EFFECT_H
*/
