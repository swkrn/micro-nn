#ifndef NEURON_H
#define NEURON_H

#include "node.h"

struct Neuron {
    struct Node *w;
    struct Node b;
    int n_in;
};

struct Neuron *neuron_alloc_n(int n, int n_in);
void neuron_init(struct Neuron *neuron, int n_in);
struct Node *neuron_exec(struct Neuron *neuron, struct Node **x, int n_in);
void neuron_print(struct Neuron *neuron, int space);

#endif
