#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "attractors.h"
#include "llist.h"
// various functions to calculate differential equations of attractors
lNode* lorenz(lNode* node) { // the classic lorenz attractor equation
	float o = 10.0f; // constant terms
	float p = 28.0f;
	float b = 8.0f/3.0f;
	float t = 0.01f; // delta, used to slow evolution of attractor equation
	float x = node->x; // temporary variables for current x y z values
	float y = node->y;
	float z = node->z;
	node->x = x + t * (o * (y - x)); // calculate differentials for next x y z
	node->y = y + t * (x * (p - z) - y);
	node->z = z + t * (x * y - b * z);
	node->px = x; // set previous x y z to current x y z
	node->py = y;
	node->pz = z;
	return node;
} 

void stepLorenz(lNode** nodeArr, int n, int div, unsigned int ID) {	
	for (int i=0; i<n; i++) {
		tailSim(nodeArr[i], ID);
		addQueue(nodeArr[i], div);
		nodeArr[i] = lorenz(nodeArr[i]);
	}
}




