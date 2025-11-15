#include "common.h"

#include <stdio.h>
#include <stdarg.h>

int *array_int(int n, ...) {
    int *array = malloc(n * sizeof(int));

    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        array[i] = va_arg(ap, int);
    };

    return array;
}
