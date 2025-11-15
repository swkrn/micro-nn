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

void mlp_print(struct MLP *mlp, int space) {
    print_space(space);
    printf("MLP(n_layer=%d)\n", mlp->n_layer);
    for (int i = 0; i < mlp->n_layer; i++) {
        layer_print(mlp->layers[i], space + 2);
    }
}
