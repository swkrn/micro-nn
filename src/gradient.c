#include "gradient.h"

void _gradient_bw(struct Node *node);

void gradient_backward(struct Node *node) {
    node->grad = 1.0;
    _gradient_bw(node);
}

void gradient_reset(struct Node *node) {
    node->grad = 0.0;

    if (!node->trace.a && !node->trace.b)
        return;

    gradient_reset(node->trace.a);
    gradient_reset(node->trace.b);
}

void _gradient_bw(struct Node *node) {
    if (!node->trace.a && !node->trace.b)
        return;

    node->trace.a->grad = node->grad * node->trace.b->value;
    node->trace.b->grad = node->grad * node->trace.a->value;

    _gradient_bw(node->trace.a);
    _gradient_bw(node->trace.b);
}
