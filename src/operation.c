#include "operation.h"

#include <math.h>

float operation_exec(float a, enum Operation oper, float b) {
    float result;

    switch (oper) {
    case NONE:
        result = 0.0;
        break;

// Binary
    case ADD:
        result = a + b;
        break;
    case MULTIPLY:
        result = a * b;
        break;

// Unary
    case TANH: {
        result = tanh(a);
        break;
    }
    }

    return result;
}
