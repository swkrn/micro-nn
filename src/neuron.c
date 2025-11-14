#include "neuron.h"

#include <assert.h>

#include "node.h"
#include "operation.h"
#include "common.h"

struct Neuron *neuron_new(int n_in) {
    struct Neuron *neuron = malloc(sizeof(struct Neuron));

    neuron->w = node_alloc_n(n_in);
    for (int i = 0; i < n_in; i++) {
        neuron->w[i].value = RAND_FLOAT(-1, 1);
    }
    neuron->b = *node_new(0.0);
    neuron->n_in = n_in;

    return neuron;
};

struct Node *neuron_exec(struct Neuron *neuron, struct Node *x, int n_in) {
    assert(neuron->n_in == n_in);

    struct Node *sum = node_new(0.0);
    for (int i = 0; i < n_in; i++) {
        struct Node *wx = node_exec((x + i), OPER_MULTIPLY, (neuron->w + i));
        sum = node_exec(sum, OPER_ADD, wx);
    }
    return sum;
}
