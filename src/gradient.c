#include "gradient.h"
#include "operation.h"

void _bw_add(struct Node *node);
void _bw_multiply(struct Node *node);

OperationBackward _backward_func[] = {
    [ADD]       = _bw_add,
    [MULTIPLY]  = _bw_multiply,
};

void _gradient_bw(struct Node *node);

void gradient_backward(struct Node *node) {
    node->grad = 1.0;
    _gradient_bw(node);
}

void gradient_reset(struct Node *node) {
    node->grad = 0.0;

    if (node->trace.a)
        gradient_reset(node->trace.a);

    if (node->trace.b)
        gradient_reset(node->trace.b);
}

// NOTE: consider this function
void _gradient_bw(struct Node *node) {
    if (node->trace.operation == NONE)
        return;

    _backward_func[node->trace.operation](node);

    if (node->trace.a)
        _gradient_bw(node->trace.a);

    if (node->trace.b)
        _gradient_bw(node->trace.b);
}

void _bw_add(struct Node *node) {
    node->trace.a->grad = node->grad;
    node->trace.b->grad = node->grad;
}

void _bw_multiply(struct Node *node) {
    node->trace.a->grad = node->grad * node->trace.b->value;
    node->trace.b->grad = node->grad * node->trace.a->value;
}
