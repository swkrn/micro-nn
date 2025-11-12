#include "src/node.h"
#include "src/gradient.h"
#include "src/operation.h"

int main() {
    struct Node *n1 = node_new(5.0);
    struct Node *n2 = node_new(2.0);
    struct Node *r = node_exec(n1, MULTIPLY, n2);

    gradient_backward(r);

    printf("%f\n", r->value);

    printf("r.grad: %f\n", r->grad);
    printf("n1.grad: %f\n", r->trace.a->grad);
    printf("n2.grad: %f\n",  r->trace.b->grad);

    gradient_reset(r);

    printf("r.grad: %f\n", r->grad);
    printf("n1.grad: %f\n", r->trace.a->grad);
    printf("n2.grad: %f\n",  r->trace.b->grad);

    return 0;
}
