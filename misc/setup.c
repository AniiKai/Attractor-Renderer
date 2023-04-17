#include "setup.h"
#include <stdio.h>

int setupWelcome() {
	printf("\t############################################################################\n\n");
	printf("\t\tWelcome to Att-R, the attractor rendering program!\n");
	printf("\t\t\t\tCreated by Bladen Sawatsky.\n\n");
	printf("\t############################################################################\n\n");
	printf("\t\t#################\n");
	printf("\t\t# RUNNING SETUP #\n");
	printf("\t\t#################\n\n");
	printf("\t\t. . .\n\n");
	printf("\t[ O ]> Enter ammount of nodes to simulate.\n");
	printf("\t[ O ]> The larger the number, the more lines will be drawn, at the cost of performance.\n\n");
	printf("\t[ I ]> Enter ammount: ");
	int n = 0;
	scanf("%d", &n);
	return n;
}

int setupRandom() {
	printf("\n\t\t. . .\n\n");
	printf("\t[ C ]> Confirmed!\n\n");
	printf("\t[ O ]> Would you like to randomize node starting positions?\n");
	printf("\t[ O ]> 0: YES, 1: NO\n\n");
	printf("\t[ I ]> Enter choice: ");
	int n = 0;
	scanf("%d", &n);
	return n;
}

int setupAttr() {
	printf("\n\t\t. . .\n\n");
	printf("\t[ C ]> Confirmed!\n\n");
	printf("\t[ O ]> Select which attractor you would like to simulate:\n\n");
	printf("\t[ O ]> 1: Lorenz,  2: example,  3: example,  4: example,  5: example,\n");
	printf("\t\t 6: example,  7: example,  8: example,  9: example\n\n");
	printf("\t[ I ]> Enter Choice: ");
	int n = 0;
	scanf("%d", &n);
	return n;
}

void setupConf() {
	printf("\n\t\t. . .\n\n");
	printf("\t[ C ]> Confirmed!\n\n");
	printf("\t[ O ]> To EXIT the simulation, press the ESC key.\n\n");
	printf("\t[ O ]> Press any key and then ENTER to start simulation...\n");
	char temp[256];
	scanf("%s", &temp);
}
