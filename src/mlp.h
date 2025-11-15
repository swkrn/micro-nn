#ifndef MLP_H
#define MLP_H

struct MLP {
    struct Layer **layers;
    int n_layer;
};

struct MLP *mlp_new(int n_in, int *n_outs, int n_outs_count);
void mlp_print(struct MLP *mlp, int space);

#endif
