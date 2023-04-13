#ifndef LLIST_H
#define LLIST_H
typedef struct tailNode { // queue node struct
	// holds all node information arranged in a way that the shader can interpret
	// 0: curr x, 1: curr y, 2: curr z, 3: prev x, 4: prev y, 5: prev z, 6: r, 7: g, 8: b, 9: a, 10 11 12 13 are copied values of previous r g b a 
	float vert[14];
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

tailNode* cons(float x, float y, float z, float px, float py, float pz, int div); // construct a new node to the heap

tailNode* addQueue(lNode* cont, int div); // queue adding function

tailNode* rmQueue(lNode* cont); // queue removal function

tailNode* rmAll(lNode* cont); // remove all existing nodes in queue
			      //
void tailSim(lNode* cont);
#endif
