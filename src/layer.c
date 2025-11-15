#include "layer.h"

#include <stdlib.h>

#include "common.h"
#include "neuron.h"

struct Layer *layer_new(int n_out, int n_in) {
    struct Layer *layer = malloc(sizeof(struct Layer));
    layer->neurons = neuron_alloc_n(n_out, n_in);
    layer->n_neuron = n_out;
    return layer;
}

struct Node **layer_exec(struct Layer *layer, struct Node *x, int n_in, int *n_out) {
    *n_out = layer->n_neuron;

    struct Node **outputs = malloc((*n_out) * sizeof(struct Node *));
    for (int i = 0; i < *n_out; i++) {
        outputs[i] = neuron_exec(&layer->neurons[i], x, n_in);
    }
    return outputs;
}

void layer_print(struct Layer *layer, int space) {
    print_space(space);
    printf("Layer(n_neuron=%d)\n", layer->n_neuron);
    for (int i = 0; i < layer->n_neuron; i++) {
        neuron_print(&layer->neurons[i], space + 2);
    }
}
