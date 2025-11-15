#include "mlp.h"

#include <stdlib.h>
#include <stdarg.h>

#include "layer.h"
#include "common.h"

struct MLP *mlp_new(int n_in, int *n_outs, int n_outs_count) {
    struct MLP *mlp = malloc(sizeof(struct MLP));

    mlp->n_layer = n_outs_count;
    mlp->layers = malloc(n_outs_count * sizeof(struct Layer *));

    for (int i = 0; i < n_outs_count; i++) {
        mlp->layers[i] = layer_new(n_outs[i], (i == 0) ? n_in : n_outs[i - 1]);
    }

    return mlp;
}

struct Node **mlp_exec(struct MLP *mlp, struct Node **x, int n_x) {
    for (int i = 0; i < mlp->n_layer; i++) {
        x = layer_exec(mlp->layers[i], x, n_x, &n_x);
    }
    struct Node **out = x;
    return out;
}

struct Node **mlp_parameters(struct MLP *mlp, int *n_params) {
    *n_params = 0;
    for (int i = 0; i < mlp->n_layer; i++) {
        struct Layer *layer = mlp->layers[i];

        for (int j = 0; j < layer->n_neuron; j++) {
            struct Neuron *neuron = &layer->neurons[j];
            *n_params += neuron->n_in;
        }
    }

    struct Node **params = malloc((*n_params) * sizeof(struct Node *));

    int counter = 0;
    struct Node **tmp_p = params;
    for (int i = 0; i < mlp->n_layer; i++) {
        struct Layer *layer = mlp->layers[i];

        for (int j = 0; j < layer->n_neuron; j++) {
            struct Neuron *neuron = &layer->neurons[j];

            for (int k = 0; k < neuron->n_in; k++) {
                *tmp_p++ = &neuron->w[k];
            }
        }
    }

    return params;
}

void mlp_print(struct MLP *mlp, int space) {
    print_space(space);
    printf("MLP(n_layer=%d)\n", mlp->n_layer);
    for (int i = 0; i < mlp->n_layer; i++) {
        layer_print(mlp->layers[i], space + 2);
    }
}
