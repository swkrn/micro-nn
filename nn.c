#include "src/neuron.h"
#include "src/node.h"

int main() {
    struct Neuron *neuron = neuron_new(3);

    struct Node *nodes = node_alloc_n(3);
    nodes[0].value = 8;
    nodes[1].value = 10;
    nodes[2].value = 5;

    printf("%f, %f, %f\n", neuron->w[0].value, neuron->w[1].value, neuron->w[2].value);

    struct Node *result = neuron_exec(neuron, nodes, 3);

    printf("result.value: %f", result->value);

    return 0;
}
