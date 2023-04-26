#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "llist.h"
#include "../shader/shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


tailNode* cons(float x, float y, float z, float px, float py, float pz, int div) { // create new tailNode
	tailNode* node = (tailNode*)malloc(sizeof(tailNode)); // check header for array map
	node->vert[0] = x/div; node->vert[1] = y/div; node->vert[2] = z/div;
	node->vert[3] = px/div; node->vert[4] = py/div; node->vert[5] = pz/div;

	node->cols[0] = x-px; 
	node->cols[1] = y-py;
	node->cols[2] = z-pz;
	node->cols[3] = 1.0f;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

lNode* newNode(float x, float y, float z) {
	lNode* node = (lNode*)malloc(sizeof(lNode));
	node->x = x; // initialize all member variables to inputs or NULL
	node->y = y;
	node->z = z;
	node->px = x;
	node->py = y;
	node->pz = z;
	node->begin = NULL;
	node->end = NULL;
	return node;
}

lNode* delNode(lNode* node) {
	rmAll(node);
	free(node);
	return NULL;
}

tailNode* addQueue(lNode* cont, int div) {
	tailNode* node = cons(cont->x, cont->y, cont->z, cont->px, cont->py, cont->pz, div);
	node->next = cont->begin;
	node->prev = NULL;
	if (cont->begin == NULL) {
		cont->begin = node;
		cont->end = node;
		return node;
	}
	cont->begin->prev = node;
	cont->begin = node;
	return node;
}

tailNode* rmQueue(lNode* cont) {
	if (cont->end == NULL) return NULL;
	if (cont->end->prev != NULL) {
		//printf("removing tail, R(%f)\n", cont->end->r);
		tailNode* t = cont->end;
		cont->end = cont->end->prev;
		cont->end->next = NULL;
		free(t);
		return cont->begin;
	}
	//printf("removing head, final node R(%f)\n", cont->begin->r);
	free(cont->begin);
	cont->end = NULL;
	cont->begin = NULL;
	return NULL;
}

tailNode* rmAll(lNode* cont) {
	tailNode* rm = rmQueue(cont);
	if (rm == NULL) return NULL;
	return rmAll(cont);
}

void tailSim(lNode* cont, unsigned int ID) {
	tailNode* curr = cont->end;
	while(curr != NULL) {
		curr->cols[3] -= 0.02f;


		glBufferData(GL_ARRAY_BUFFER, sizeof(curr->vert), curr->vert, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		setCols(ID, "ins", curr->cols);
			
		glDrawArrays(GL_LINES, 0, 2);

		if (curr->cols[3] <= 0.0f) {
			rmQueue(cont);
		}
		// here is where you would render the tail as a line in glfw
		curr = curr->prev;
	}
}
void visualizeTest(lNode* cont, unsigned int ID) {
	tailNode* curr = cont->end;
	while(curr != NULL) {
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(curr->vert), curr->vert, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		setCols(ID, "ins", curr->cols);
			
		glDrawArrays(GL_LINES, 0, 2);
		curr = curr->prev;
	}
}
