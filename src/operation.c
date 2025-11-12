#include "operation.h"

float operation_exec(float a, enum Operation oper, float b) {
    float result;
    switch (oper) {
    case NONE:
        result = 0.0;
        break;
    case ADD:
        result = a + b;
        break;
    case MULTIPLY:
        result = a * b;
        break;
    }
    return result;
}
