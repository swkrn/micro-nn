#ifndef OPERATION_H
#define OPERATION_H

enum Operation {
    NONE = 0,
    ADD,
    MULTIPLY,
};

float operation_exec(float a, enum Operation oper, float b);

#endif
