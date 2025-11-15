#include "gradient.h"

#include <math.h>

#include "operation.h"

void _gradient_bw(struct Node *node);

void gradient_backward(struct Node *node) {
    node->grad = 1.0;
    _gradient_bw(node);
}

void gradient_reset(struct Node *node) {
    node->grad = 0.0;
    node->visted = false;

    if (node->trace.a)
        gradient_reset(node->trace.a);

    if (node->trace.b)
        gradient_reset(node->trace.b);
}

void _gradient_bw(struct Node *node) {
    if (node->trace.operation == OPER_NONE)
        return;

    if (node->visted) {
        goto trace_label;
    }
    node->visted = true;

    const float r_grad = node->grad;
    const float r = node->value;

    float *a_grad = &node->trace.a->grad;
    float *b_grad = (node->trace.b) ? &node->trace.b->grad : NULL;

    const float a = node->trace.a->value;
    const float b = (node->trace.b) ? node->trace.b->value : 0;

    switch (node->trace.operation) {
    case OPER_NONE:
        break;

// Binary
    case OPER_ADD:
    case OPER_SUB:
        *a_grad += r_grad;
        *b_grad += r_grad;
        break;
    case OPER_MULTIPLY:
        *a_grad += r_grad * b;
        *b_grad += r_grad * a;
        break;
    case OPER_POW: {
        *a_grad += r_grad * (b * pow(a, b - 1));
        *b_grad += r_grad * (r * log(a));
        break;
    }

// Unary
    case OPER_TANH: {
        *a_grad += r_grad * (1 - pow(r, 2));
        break;
    }
    }

trace_label:
    if (node->trace.a)
        _gradient_bw(node->trace.a);

    if (node->trace.b)
        _gradient_bw(node->trace.b);
}
