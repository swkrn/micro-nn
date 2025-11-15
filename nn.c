#include "src/layer.h"
#include "src/mlp.h"
#include "src/common.h"

#include <stdbool.h>

int main() {
    const int n_input = 3;
    const int n_outs_count = 2;
    int *n_outs  = array_int(n_outs_count, 1, 5);

    struct MLP *mlp = mlp_new(n_input, n_outs, n_outs_count);
    mlp_print(mlp);

    return 0;
}
