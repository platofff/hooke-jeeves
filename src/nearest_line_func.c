// https://www.mallenom.ru/company/publications/324/
// Минимизируемая функция
#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "hnj.h"

int prepare() {
    fputs("Количество точек: ", stdout);
    if (scanf("%lu", &points_size) != 1)
    {
        fputs("Некорректное количество точек!\n", stderr);
        return -1;
    }
    points = malloc(sizeof(Point) * points_size);
    for (unsigned i = 0; i < points_size; i++)
    {
        printf("Координаты точки %u: ", i + 1);
        if (scanf("%Lf %Lf", &points[i].x, &points[i].y) != 2)
        {
            fputs("Некорректные координаты точки!\n", stderr);
            return -1;
        }
    }
    return 0;
}

int finish() {
    free(points);
    char b_sym[2] = {'\0', '\0'};
    if (current.b >= 0.0)
    {
        b_sym[0] = '+';
    }
    printf("y=%.3Lfx%s%.3Lf\n", current.a, b_sym, current.b);
    return 0;
}

long double func(long double a, long double b)
{
    long double sum = 0.0L;
    for (unsigned i = 0; i < points_size; i++)
    {
        long double tmp = points[i].y - a * points[i].x - b;
        sum += tmp * tmp;
    }
    return sum;
}
