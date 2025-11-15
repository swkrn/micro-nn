#include "src/layer.h"
#include "src/mlp.h"
#include "src/common.h"
#include "src/node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    const int n_input = 3;
    const int n_outs_count = 2;
    const int n_output = 1;

    int *n_outs  = array_int(n_outs_count, 2, n_output);

    struct Node **x = malloc(n_input * sizeof(struct Node *));
    for (int i = 0; i < n_input; i++) {
        x[i] = node_new((i + 1) * 2);
    }

    struct MLP *mlp = mlp_new(n_input, n_outs, n_outs_count);
    mlp_print(mlp, 0);
    struct Node **out = mlp_exec(mlp, x, n_input);

    for (int i = 0; i < n_output; i++) {
        printf("out[%d]: %f\n", i, out[i]->value);
    }

    return 0;
}
