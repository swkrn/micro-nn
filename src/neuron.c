#include "neuron.h"

#include <assert.h>

#include "node.h"
#include "operation.h"
#include "common.h"

struct Neuron *neuron_alloc_n(int n, int n_in) {
    struct Neuron *neurons = malloc(n * sizeof(struct Neuron));
    for (int i = 0; i < n; i++) {
        neuron_init(&neurons[i], n_in);
    }
    return neurons;
}

void neuron_init(struct Neuron *neuron, int n_in) {
    neuron->w = node_alloc_n(n_in);
    for (int i = 0; i < n_in; i++) {
        neuron->w[i].value = RAND_FLOAT(-1, 1);
    }
    neuron->b = *node_new(0.0);
    neuron->n_in = n_in;
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

void neuron_print(struct Neuron *neuron) {
    printf("        Neuron(n_in=%d, b=%f)\n", neuron->n_in, neuron->b.value);
    for (int i = 0; i < neuron->n_in; i++) {
        printf("        → w[%d] = %f\n", i, neuron->w[i].value);
    }
}
