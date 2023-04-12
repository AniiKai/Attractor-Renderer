#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "llist.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


tailNode* cons(float x, float y, float z, float px, float py, float pz, int div) { // create new tailNode
	tailNode* node = (tailNode*)malloc(sizeof(tailNode));
	node->x = x/div; node->y = y/div; node->z = z/div;
	node->px = px/div; node->py = py/div; node->pz = pz/div;
	float dx = x-px;
	float dy = y-py;
	float dz = z-pz;
	float vel = sqrt(dx*dx + dy*dy + dz*dz);
	if (vel < 1.0f) { // map colors to speed
		node->r = 0.0f;
		node->g = vel;
		node->b = 1.0f;
	}
	else if (vel < 2.0f) {
		node->r = 0.0f;
		node->g = 1.0f;
		node->b = 2.0f - vel;
	}
	else if (vel < 3.0f) {
		node->r = vel - 2.0f;
		node->g = 1.0f;
		node->b = 0.0f;
	}
	else if (vel < 4.0f) {
		node->r = 1.0f;
		node->g = 4.0f - vel;
		node->b = 0.0f;	
	}
	else if (vel < 5.0f) {
		node->r = 1.0f;
		node->g = 0.0f;
		node->b = vel - 4.0f;
	}
	else {
		node->r = 1.0f;
		node->g = 0.0f;
		node->b = 1.0f;
	}

	node->a = 1.0f;
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

void tailSim(lNode* cont) {
	tailNode* curr = cont->end;
	while(curr != NULL) {
		curr->a -= 0.01f;
		
		float vertices[14];
		vertices[0] = curr->px; vertices[1] = curr->py; vertices[2] = curr->pz;
		vertices[3] = curr->x; vertices[4] = curr->y; vertices[5] = curr->z;
		vertices[6] = curr->r; vertices[7] = curr->g; vertices[8] = curr->b; vertices[9] = curr->a;
		vertices[10] = curr->r; vertices[11] = curr->g; vertices[12] = curr->b; vertices[13] = curr->a;


		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(1);
	
		glDrawArrays(GL_LINES, 0, 2);

		if (curr->a <= 0.0f) {
			rmQueue(cont);
		}
		// here is where you would render the tail as a line in glfw
		curr = curr->prev;
	}
}
