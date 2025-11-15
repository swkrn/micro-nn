#ifndef MLP_H
#define MLP_H

struct MLP {
    struct Layer **layers;
    int n_layer;
};

struct MLP *mlp_new(int n_in, int *n_outs, int n_outs_count);
struct Node **mlp_exec(struct MLP *mlp, struct Node **x, int n_x);
struct Node **mlp_parameters(struct MLP *mlp, int *n_params);
void mlp_print(struct MLP *mlp, int space);

#endif
