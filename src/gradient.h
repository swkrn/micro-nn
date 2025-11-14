#ifndef GRADIENT_H
#define GRADIENT_H

#include "node.h"
#include "operation.h"

void gradient_backward(struct Node *node);
void gradient_reset(struct Node *node);

#endif
