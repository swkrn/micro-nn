#include "src/neuron.h"
#include "src/node.h"

int main() {
    const int n_neuron  = 2;
    const int n_input = 3;

    struct Neuron *neurons = neuron_alloc_n(n_neuron, n_input);

    struct Node *nodes = node_alloc_n(n_input);
    for (int i = 0; i < n_input; i++) {
        nodes[i].value = (i + 1) * 2;
    }

    for (int i = 0; i < n_neuron; i++) {
        for (int j = 0; j < n_input; j++)
        printf("neuron->neuron[%d].w[%d]: %f\n", i, j, neurons[i].w[j].value);
    }

    struct Node *result = neuron_exec(neurons, nodes, 3);

    printf("result.value: %f", result->value);

    return 0;
}
