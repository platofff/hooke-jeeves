#include <stddef.h>

typedef struct
{
    long double x, y;
} Point;

int prepare();
long double func(long double a, long double b);
int finish();

extern size_t points_size;
extern Point *points;
