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
lNode* halvorsen(lNode* node) {
	float a = 1.4f;
	float t = 0.005f;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * (-1*a*x - 4*y - 4*z - y*y);
	node->y = y + t * (-1*a*y - 4*z - 4*x - z*z);
	node->z = z + t * (-1*a*z - 4*x - 4*y - x*x);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;
}

lNode* aizawa(lNode* node) {
	float a = 0.95f;
	float b = 0.7f;
	float c = 0.6f;
	float d = 3.5f;
	float e = 0.25f;
	float f = 0.1f;
	float t = 0.01f;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * ((z - b)*x - d*y);
	node->y = y + t * (d*x + (z - b)*y);
	node->z = z + t * (c + a*z - z*z*z/3.0f - (x*x + y*y) * (1 + e*z) + f*z*x*x*x);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;
}

lNode* fourWing(lNode* node) {
	float a = 4.0f;
	float b = 6.0f;
	float c = 10.0f;
	float d = 5.0f;
	float k = 1.0f;
	float t = 0.005f;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * (a*x - b*y*z);
	node->y = y + t * (-1.0f*c*y + x*z);
	node->z = z + t * (k*x - d*z + x*y);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;
}

lNode* dadras(lNode* node) {
	float p = 3.0f;
	float q = 2.7f;
	float r = 1.7f;
	float s = 2.0f;
	float e = 9.0f;
	float t = 0.01;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * (y - p*x + q*y*z);
	node->y = y + t * (r*y - x*z + z);
	node->z = z + t * (s*x*y - e*z);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;

}

lNode* zhouChen(lNode* node) {
	float a = 2.97f;
	float b = 0.15f;
	float c = -3.0f;
	float d = 1.0f;
	float e = -8.78f;
	float t = 0.002f;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * (a*x + b*y + y*z);
	node->y = y + t * (c*y - x*z + d*y*z);
	node->z = z + t * (e*z - x*y);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;
}

lNode* thomas(lNode* node) {
	float b = 0.19f;
	float t = 0.1f;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * (-1*b*x + sin(y));
	node->y = y + t * (-1*b*y + sin(z));
	node->z = z + t * (-1*b*z + sin(x));
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;
}

lNode* rayleighBernard(lNode* node) {
	float a = 9.0f;
	float r = 12.0f;
	float b = 5.0f;
	float t = 0.05f;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * (-1*a*x + a*y);
	node->y = y + t * (r*x - y - x*z);
	node->z = z + t * (x*y - b*z);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;
	
}

lNode* cells(lNode* node) {
	float x = node->x;
	float y = node->y;
	float z = node->z;
	float h1 = 0.5f * (fabs(x+1) - fabs(x-1));
	float h2 = 0.5f * (fabs(y+1) - fabs(y-1));
	float h3 = 0.5f * (fabs(z+1) - fabs(z-1));
	float p1 = 1.24f;
	float p2 = 1.1f;
	float r = 4.4f;
	float s = 3.21f;
	float t = 0.007f;
	node->x = x + t * (-1*x + p1*h1 - s*h2 - s*h3);
	node->y = y + t * (-1*y - s*h1 + p2*h2 - r*h3);
	node->z = z + t * (-1*z - s*h1 + r*h2 + h3);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;
}

lNode* bouali(lNode* node) {
	float a = 0.3f;
	float s = 1.0f;
	float t = 0.006f;
	float x = node->x;
	float y = node->y;
	float z = node->z;
	node->x = x + t * (x*(4.0f - y) + a*z);
	node->y = y + t * (-1*y*(1 - x*x));
	node->z = z + t * (-1*x*(1.5f - s*z) - 0.05f*z);
	node->px = x;
	node->py = y;
	node->pz = z;
	return node;

}

void stepAttr(lNode** nodeArr, int n, int div, unsigned int ID, int choice) {	
	for (int i=0; i<n; i++) {
		tailSim(nodeArr[i], ID);
		addQueue(nodeArr[i], div);
		switch (choice) {
			case 1:
				nodeArr[i] = lorenz(nodeArr[i]);
				break;
			case 2:
				nodeArr[i] = halvorsen(nodeArr[i]);
				break;
			case 3:
				nodeArr[i] = aizawa(nodeArr[i]);
				break;
			case 4:
				nodeArr[i] = fourWing(nodeArr[i]);
				break;
			case 5:
				nodeArr[i] = dadras(nodeArr[i]);
				break;
			case 6:
				nodeArr[i] = zhouChen(nodeArr[i]);
				break;
			case 7:
				nodeArr[i] = thomas(nodeArr[i]);
				break;
			case 8:
				nodeArr[i] = rayleighBernard(nodeArr[i]);
				break;
			case 9:
				nodeArr[i] = cells(nodeArr[i]);
				break;
			case 10:
				nodeArr[i] = bouali(nodeArr[i]);
				break;
			default:
				nodeArr[i] = lorenz(nodeArr[i]);
				break;
		}
	}
}

float sizeTest(lNode** nodeArr, int n, int choice, float max) {
	for (int i=0; i<n; i++) {
		switch (choice) {
			case 1:
				nodeArr[i] = lorenz(nodeArr[i]);
				break;
			case 2:
				nodeArr[i] = halvorsen(nodeArr[i]);
				break;
			case 3:
				nodeArr[i] = aizawa(nodeArr[i]);
				break;
			case 4:
				nodeArr[i] = fourWing(nodeArr[i]);
				break;
			case 5:
				nodeArr[i] = dadras(nodeArr[i]);
				break;
			case 6:
				nodeArr[i] = zhouChen(nodeArr[i]);
				break;
			case 7:
				nodeArr[i] = thomas(nodeArr[i]);
				break;
			case 8:
				nodeArr[i] = rayleighBernard(nodeArr[i]);
				break;
			case 9:
				nodeArr[i] = cells(nodeArr[i]);
				break;
			case 10:
				nodeArr[i] = bouali(nodeArr[i]);
				break;
			default:
				nodeArr[i] = lorenz(nodeArr[i]);
				break;
		}
		if (fabs(nodeArr[i]->x) > max) max = fabs(nodeArr[i]->x);
		if (fabs(nodeArr[i]->y) > max) max = fabs(nodeArr[i]->y);
		if (fabs(nodeArr[i]->z) > max) max = fabs(nodeArr[i]->z);
	}
	return max;
}


