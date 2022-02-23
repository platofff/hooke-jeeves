#include <stdbool.h>

typedef struct
{
    long double a, b;
} Step;

typedef struct
{
    long double a, b, value;
} Params;

// Параметры метода Хука-Дживса
static Params start = {1.0, 1.0L, 0.0L};
static long double accuracy = 0.00001L;
static Step start_step = {1.0L, 1.0L};
static long double lambda = 2.0L;

extern Params current;

void first_phase(Step step);
bool hnj_iter(long double *_current, long double another, long double *value, long double _step, bool is_a);
