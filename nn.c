#include "src/node.h"
#include "src/gradient.h"
#include "src/operation.h"

int main() {
    struct Node *x1 = node_new(5.0);
    struct Node *w1 = node_new(2.0);

    struct Node *x1w1 = node_exec(x1, MULTIPLY, w1);

    struct Node *x2 = node_new(20.0);
    struct Node *w2 = node_new(10.0);

    struct Node *x2w2 = node_exec(x2, MULTIPLY, w2);

    struct Node *x1w1_x2w2 = node_exec(x1w1, ADD, x2w2);

    gradient_backward(x1w1_x2w2);

    printf("%f\n", x1w1_x2w2->value);

    printf("y.grad: %f\n", x1w1_x2w2->grad);

    printf("x1.grad: %f\n", x1->grad);
    printf("w1.grad: %f\n",  w1->grad);

    printf("x2.grad: %f\n", x2->grad);
    printf("w2.grad: %f\n",  w2->grad);

    gradient_reset(x1w1_x2w2);

    printf("x1.grad: %f\n", x1->grad);
    printf("w1.grad: %f\n",  w1->grad);

    printf("x2.grad: %f\n", x2->grad);
    printf("w2.grad: %f\n",  w2->grad);

    return 0;
}
