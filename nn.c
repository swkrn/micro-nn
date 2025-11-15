#include "src/layer.h"
#include "src/neuron.h"
#include "src/node.h"

#include <stdbool.h>

int main() {
    const int n_neuron  = 2;
    const int n_input = 3;

    struct Node *x = node_alloc_n(n_input);
    for (int i = 0; i < n_input; i++) {
        x[i].value = (i + 1) * 2;
        node_print(&x[i], true);
    }

    struct Neuron *neuron = neuron_alloc_n(1, 2);
    for (int i = 0; i < 2; i++) {
        neuron_print(&neuron[i]);
    }

    struct Layer *layer = layer_new(n_neuron, n_input);
    layer_print(layer);

    int n_out;
    struct Node **o = layer_exec(layer, x, n_input, &n_out);
    for (int i = 0; i < n_out; i++) {
        printf("o[%d].value: %f\n", i, o[i]->value);
    }

    return 0;
}
