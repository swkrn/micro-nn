#include "node.h"

#include "operation.h"

struct Node *node_new(float value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    node_init(new_node);
    new_node->value = value;
    return new_node;
}

struct Node *node_alloc_n(int n) {
    struct Node *nodes = malloc(n * sizeof(struct Node));
    while (n--) {
        node_init(&nodes[n]);
    }
    return nodes;
}

struct Node *node_exec(
    struct Node *a,
    enum Operation oper,
    struct Node *b
) {
    float new_value = operation_exec(a->value, oper, (b) ? b->value : 0);
    struct Node *new_node = node_new(new_value);

    new_node->trace.a = a;
    new_node->trace.operation = oper;
    new_node->trace.b = b;

    return new_node;
}

void node_init(struct Node *node) {
    node->value = 0;
    node->grad = 0;

    node->trace.a = NULL;
    node->trace.operation = OPER_NONE;
    node->trace.b = NULL;
}

void node_print(struct Node *node, bool showTrace) {
    printf("Node(%f, grad=%f)", node->value, node->grad);

    if (showTrace) {
        if (node->trace.operation == OPER_NONE) {
            goto out;
        }
        const float a = node->trace.a->value ;
        const float b = (node->trace.b) ? node->trace.b->value : 0.0;

        printf(" [");
        switch (node->trace.operation) {
        case OPER_NONE:
            break;
        case OPER_ADD:
            printf("%f + %f\n", a, b);
            break;
        case OPER_SUB:
            printf("%f - %f\n", a, b);
            break;
        case OPER_MULTIPLY:
            printf("%f * %f\n", a, b);
            break;
        case OPER_POW:
            printf("pow(%f, %f)\n", a, b);
            break;
        case OPER_TANH:
            printf("tanh(%f)\n", a);
        break;
        }
        printf("]\n");
    } else {
out:
        printf("\n");
    }
}
