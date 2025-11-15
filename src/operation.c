#include "operation.h"

#include <math.h>

float operation_exec(float a, enum Operation oper, float b) {
    float result;

    switch (oper) {
    case OPER_NONE:
        result = 0.0;
        break;

// Binary
    case OPER_ADD:
        result = a + b;
        break;
    case OPER_SUB:
        result = a - b;
        break;
    case OPER_MULTIPLY:
        result = a * b;
        break;
    case OPER_POW: {
        result = pow(a, b);
        break;
    }

// Unary
    case OPER_TANH: {
        result = tanh(a);
        break;
    }
    }

    return result;
}
