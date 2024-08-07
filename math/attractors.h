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

lNode* roessler(lNode* node);

lNode* gravitational(lNode** node, int i, int n);

lNode* sierpinskiDifferential(lNode* node);

void stepGravity(lNode** nodeArr, int n, int div, unsigned int ID);

void runSim(lNode** nodeArr, int n, int div, unsigned int ID, int choice); // calculate a step + render it

void stepAttr(lNode* nodeArr, int div, int choice); // calculate a step of a chaotic system
								   //
float sizeTest(lNode** nodeArr, int n, int div, int choice, float max);
#endif
