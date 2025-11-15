#include "neuron.h"

struct Layer {
    struct Neuron *neurons;
    int n_neuron;
};

struct Layer *layer_new(int n_neuron, int n_in);
struct Node **layer_exec(struct Layer *layer, struct Node *x, int n_in, int *n_out);
void layer_print(struct Layer *layer);
