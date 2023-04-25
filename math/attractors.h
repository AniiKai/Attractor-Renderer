#ifndef ATTRACTORS_H
#define ATTRACTORS_H
#include "llist.h"
#include <cglm/cglm.h>
typedef struct structArgs {
	lNode** nodeArr;
	int begin;
	int end;
	int div;
	unsigned int ID;

} structArgs;

lNode* lorenz(lNode* node); // classic lorenz attractor

lNode* halvorsen(lNode* node);

lNode* aizawa(lNode* node);

lNode* fourWing(lNode* node);

lNode* dadras(lNode* node);

lNode* zhouChen(lNode* node);

lNode* thomas(lNode* node);

lNode* rayleighBernard(lNode* node);

lNode* cells(lNode* node);

lNode* bouali(lNode* node);

lNode* chenLee(lNode* node);

void stepAttr(lNode** nodeArr, int n, int div, unsigned int ID, int choice); // calculate a step of the lorenz system
								   //
float sizeTest(lNode** nodeArr, int n, int choice, float max);
#endif
