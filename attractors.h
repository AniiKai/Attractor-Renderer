#ifndef ATTRACTORS_H
#define ATTRACTORS_H
#include "llist.h"
lNode* lorenz(lNode* node); // classic lorenz attractor

void stepLorenz(lNode** nodeArr, int n); // calculate a step of the lorenz system
#endif
