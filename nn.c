#include "mnist/reader.h"
#include "src/gradient.h"
#include "src/mlp.h"
#include "src/common.h"
#include "src/node.h"
#include "src/operation.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// -1 to 1
float normalize(int value, int min, int max) {
    return (((float)(value - min) / (float)(max - min)) * 2) - 1;
}

int main() {
    srand(time(NULL));

    const int n_layer = 3;

    struct Images train_mnist;
    reader_read_images(
        "mnist/dataset/train-images.idx3-ubyte",
        "mnist/dataset/train-labels.idx1-ubyte",
        &train_mnist
    );
    reader_show_images(&train_mnist, 0, 10);

    const int n_train = 1000;

    struct MLP *mlp = mlp_new(
        train_mnist.each_size,
        array_int(n_layer, 20, 10, 1),
        n_layer
    );

    int n_params;
    struct Node **params = mlp_parameters(mlp, &n_params);

    struct Node **labels_true = malloc(n_train * sizeof(struct Node *));
    for (int img_index = 0; img_index < n_train; img_index++) {
        labels_true[img_index] = node_new(normalize(train_mnist.labels[img_index], 0, 9));
    }
    struct Node ***labels_pred = malloc(n_train * sizeof(struct Node **));

    struct Node *loss = node_new(0);
    for (int iter = 0; iter < 20; iter++) {
        // forward pass
        for (int img_index = 0; img_index < n_train; img_index++) {
             uint8_t *image = train_mnist.images[img_index];

            // normalize
            struct Node **normalized_image = malloc(train_mnist.each_size * sizeof(struct Node *));

            // printf("\n - [%2d] image index: %d\n", iter, img_index);
            for (int pixel = 0; pixel < train_mnist.each_size; pixel++) {
                normalized_image[pixel] = node_new(normalize(image[pixel], 0, 255));
            }

            labels_pred[img_index] = mlp_exec(mlp, normalized_image, train_mnist.each_size);
            loss = node_exec(
                loss,
                OPER_ADD,
                node_exec(
                    node_exec(
                        labels_true[img_index], OPER_SUB, labels_pred[img_index][0]),
                        OPER_POW,
                        node_new(2)
                )
            );
        }

        // backward pass
        gradient_reset(loss);
        gradient_backward(loss);

        // update parameters
        for (int i = 0; i < n_params; i++) {
            params[i]->value += 0.001 * params[i]->grad;
        }

        // print samples
        printf("[%2d] loss: %f\n", iter, loss->value);
        for (int img_index = 0; img_index < 10; img_index++) {
            printf("     [%2d] ", img_index);
            // node_print(y_pred[i][0], 0);
            printf("y: %f, y_pred: %f\n", labels_true[img_index]->value, labels_pred[img_index][0]->value);
        }
        // mlp_print(mlp, 4);
        printf("--------------------\n");

    }

    return 0;
}
