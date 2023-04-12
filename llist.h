#ifndef LLIST_H
#define LLIST_H
typedef struct tailNode { // queue node struct
	float x, y, z; // current position of parent lNode at creation
	float px, py, pz; // previous position of parent lNode at creation
	float r;
	float g;
	float b;
	float a;
	struct tailNode* next; 
	struct tailNode* prev; 
} tailNode;

typedef struct lNode { // queue container 
	float x, y, z; // holds 2 coordinates, current position, and previous position
	float px, py, pz;
	tailNode* begin; // all tailNodes belonging to current node
	tailNode* end; 
} lNode;

lNode* newNode(float x, float y, float z);

lNode* delNode(lNode* node);

tailNode* cons(float x, float y, float z, float px, float py, float pz); // construct a new node to the heap

tailNode* addQueue(lNode* cont); // queue adding function

tailNode* rmQueue(lNode* cont); // queue removal function

tailNode* rmAll(lNode* cont); // remove all existing nodes in queue
			      //
void tailSim(lNode* cont);
#endif
