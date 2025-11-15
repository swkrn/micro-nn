#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

#define RAND_FLOAT(min, max) ((max - min) * ((float)rand() / RAND_MAX)) + min

int *array_int(int n, ...);

#endif
