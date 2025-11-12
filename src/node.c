#include "node.h"

#include "operation.h"

struct Node *node_new(float value) {
    struct Node *new_node = malloc(sizeof(struct Node));

    new_node->value = value;
    new_node->grad = 0;

    new_node->trace.a = NULL;
    new_node->trace.operation = NONE;
    new_node->trace.b = NULL;
    return new_node;
}

struct Node *node_exec(
    struct Node *a,
    enum Operation oper,
    struct Node *b
) {
    float new_value = operation_exec(a->value, oper, b->value);
    struct Node *new_node = node_new(new_value);

    new_node->trace.a = a;
    new_node->trace.b = b;
    new_node->trace.operation = oper;

    return new_node;
}
