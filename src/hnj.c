// https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%A5%D1%83%D0%BA%D0%B0_%E2%80%94_%D0%94%D0%B6%D0%B8%D0%B2%D1%81%D0%B0
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <tgmath.h>
#include <float.h>
#include "func.h"
#include "hnj.h"

size_t points_size = 0;
Point *points = NULL;
Params current = {0};

void first_phase(Step step)
{
    while (sqrtl(step.a * step.a + step.b * step.b) >= accuracy)
    { // Повторять пока корень суммы шагов по обоим координатам не станет меньше точности
        if (!hnj_iter(&(current.a), current.b, &(current.value), step.a, 1))
        { // Изменяем a так, чтобы значение функции уменьшилось. Если нельзя это сделать, то уменьшаем шаг по a
            step.a /= 2.0L;
        }
        if (!hnj_iter(&(current.b), current.a, &(current.value), step.b, 0))
        { // Аналогично с b
            step.b /= 2.0L;
        }
    }
}

/*
      Итерация метода Хука-Дживса
        *_current - указатель на параметр функции, который подлежит изменению
        another - замороженный параметр функции
        *value - указатель на значение функции
        _step - шаг изменения изменяемого параметра функции
        is_a - является ли изменяемый параметр a
*/
bool hnj_iter(long double *_current, long double another, long double *value, long double _step, bool is_a)
{
    long double up = *_current + _step,                                // Значение параметра при увеличении на шаг
        down = *_current - _step,                                      // Значение параметра при уменьшении на шаг
        up_value = is_a ? func(up, another) : func(another, up),       // Значение функции с увеличенным параметром
        down_value = is_a ? func(down, another) : func(another, down); // Значение функции с уменьшенным параметром
    if (up_value < down_value && up_value < *value)
    { // Если значение функции с увеличенным параметром ниже, сохраняем увеличенный параметр и новое значение функции
        *value = up_value;
        *_current = up;
    }
    else if (down_value < up_value && down_value < *value)
    { // Аналогично с уменьшенным параметром
        *value = down_value;
        *_current = down;
    }
    else
    { // Если исходное значение функции меньше и значения с увеличенным параметром, и значения с уменьшенным параметром, возвращаем ошибку
        return 0;
    }
    return 1;
}

int main()
{
    int res = prepare();
    if (res != 0) {
        return res;
    }

    // 1-я фаза

    start.value = func(start.a, start.b); // Определяем значение функции для стартовой точки
    current = start;

    first_phase(start_step);
    /* 2-я фаза
        x1 - start
        x2 - current */
    while (1)
    {
        Params x3 = {start.a + lambda * (current.a - start.a), start.b + lambda * (current.b - start.b), 0.0L}; // x₃ = x₁ + λ(x₂ - x₁)
        x3.value = func(x3.a, x3.b);
        Params x4 = x3;
        while (hnj_iter(&x4.a, x4.b, &x4.value, start_step.a, 1) || hnj_iter(&x4.b, x4.a, &x4.value, start_step.b, 0))
        {
        } // Повторяем первую фазу не уменьшая шаг
        if (x4.a > x3.a + LDBL_EPSILON || x4.a < x3.a - LDBL_EPSILON || x4.b > x3.b + LDBL_EPSILON || x4.b < x3.b - LDBL_EPSILON)
        {                    // Удалось найти точку x4, отличную от x3
            start = current; // x1 принимает значение x2
            current = x4;    // x2 принимает значение x4
        }
        else
        { // Не удалось найти точку x4, отличную от x3, прекращение итераций
            break;
        }
    }

    start = current;         // x1 принимает значение x2
    first_phase(start_step); // повторение 1-й фазы

    return finish();
}
