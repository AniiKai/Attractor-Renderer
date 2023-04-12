#include "math/llist.h"
#include "math/attractors.h"
#include <stdlib.h>
#include <stdio.h> 
int main(void) {
	int n = 100;
	lNode** contArr = malloc(n * sizeof(lNode*));
	float ix = 0.01f;
	float iy = 0.01f;
	float iz = 0.01f;
	//printf("creating simulation nodes.\n");
	for (int i=0; i<n; i++) {
		contArr[i] = newNode(ix, iy, iz); // initialize all nodes in array
		//printf("X: %f, Y: %f, Z: %f\n", contArr[i]->x, contArr[i]->y, contArr[i]->z);
		ix += 0.01f;
		iy += 0.01f;
		iz += 0.01f;
	}
	//printf("starting simulation..\n");
	for (int i=0; i<10000; i++) {
		//printf("frame: %d\n", i);
		stepLorenz(contArr, n);
	}
	/*
	printf("printing final values..\n");
	for (int i=0; i<n; i++) {
		printf("X: %f, Y: %f, Z: %f\n", contArr[i]->x, contArr[i]->y, contArr[i]->z);
	}
	printf("freeing memory and closing program\n");
	*/
	for (int i=0; i<n; i++) {
		delNode(contArr[i]);
	}
	free(contArr);
	
	
	return 0;
}
