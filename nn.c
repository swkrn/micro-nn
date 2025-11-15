#include "src/gradient.h"
#include "src/layer.h"
#include "src/mlp.h"
#include "src/common.h"
#include "src/node.h"
#include "src/operation.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_INPUT 3
#define DATA_COUNT 4

int main() {
    srand(time(NULL));

    const int n_outs_count = 3;

    struct Node *x[DATA_COUNT][N_INPUT] = {
       {node_new(2.0), node_new(3.0), node_new(-1.0)},
       {node_new(3.0), node_new(-1.0), node_new(0.5)},
       {node_new(0.5), node_new(1.0), node_new(1.0)},
       {node_new(1.0), node_new(1.0), node_new(-1.0)},
    };

    struct Node *y[DATA_COUNT] = {
        node_new(1.0),
        node_new(-1.0),
        node_new(-1.0),
        node_new(1.0),
    };

    struct MLP *mlp = mlp_new(N_INPUT, array_int(n_outs_count, 4, 4, 1), n_outs_count);

    struct Node ***y_pred = malloc(DATA_COUNT * sizeof(struct Node **));

    int n_params;
    struct Node **params = mlp_parameters(mlp, &n_params);
    printf("n_params: %d\n", n_params);
    mlp_print(mlp, 0);

    printf("\n");

    for (int i = 0; i < 20; i++) {
        // forward pass
        struct Node *loss = node_new(0.0);
        for (int j = 0; j < DATA_COUNT; j++) {
            y_pred[j] = mlp_exec(mlp, x[j], N_INPUT);
            loss = node_exec(
                loss,
                OPER_ADD,
                node_exec(
                    node_exec(y[j], OPER_SUB, y_pred[j][0]),
                    OPER_POW,
                    node_new(2)
                )
            );
        }

        // backward pass
        gradient_reset(loss);
        gradient_backward(loss);

        // update parameters
        for (int j = 0; j < n_params; j++) {
            params[j]->value += 0.1 * params[j]->grad;
        }

        printf("[%2d] loss: %f\n", i, loss->value);
        for (int i = 0; i < DATA_COUNT; i++) {
            printf("    [%d] ", i);
            // node_print(y_pred[i][0], 0);
            printf("y: %f, y_pred: %f\n", y[i]->value, y_pred[i][0]->value);
        }
        // mlp_print(mlp, 4);
        printf("--------------------\n");
    }

    return 0;
}
