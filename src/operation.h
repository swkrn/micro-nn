#ifndef OPERATION_H
#define OPERATION_H

enum Operation {
    OPER_NONE = 0,

    // Binary
    OPER_ADD,
    OPER_SUB,
    OPER_MULTIPLY,
    OPER_POW,

    // Unary
    OPER_TANH,
};

float operation_exec(float a, enum Operation oper, float b);

#endif
