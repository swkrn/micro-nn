#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "operation.h"

struct Trace {
    struct Node *a;
    enum Operation operation;
    struct Node *b;
};

struct Node {
    float value;
    float grad;
    struct Trace trace;
};

struct Node *node_new(float value);

struct Node *node_alloc_n(int n);

struct Node *node_exec(
    struct Node *a,
    enum Operation oper,
    struct Node *b
);

void node_init(struct Node *node);

void node_print(struct Node *node, bool showTrace);

#endif
