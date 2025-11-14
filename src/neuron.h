#ifndef NEURON_H
#define NEURON_H

#include "node.h"

struct Neuron {
    struct Node *w;
    struct Node b;
    int n_in;
};

struct Neuron *neuron_new(int n_in);
struct Node *neuron_exec(struct Neuron *neuron, struct Node *x, int n_in);

#endif
