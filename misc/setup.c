#include "setup.h"
#include <stdio.h>

int setupWelcome() {
	printf("\t############################################################################\n\n");
	printf("\t\tWelcome to Att-R, the attractor rendering program!\n");
	printf("\t\t\t\tCreated by Bladen Sawatsky.\n\n");
	printf("\t############################################################################\n\n\n");
	printf("\t##### RUNNING SETUP #####\n\n");
	printf("\t[ O ]> Enter ammount of nodes to simulate.\n");
	printf("\t[ O ]> The larger the number, the more lines will be drawn, at the cost of performance.\n\n");
	printf("\t[ I ]> Enter amount: ");
	int n = 0;
	scanf("%d", &n);
	return n;
}

int setupFS() {
	printf("\n\t\t. . .\n\n");
	printf("\t[ O ]> Confirmed!\n\n");
	printf("\t[ O ]> Would you like to run in full-screen?\n");
	printf("\t[ O ]> 0: YES, 1: NO\n\n");
	printf("\t[ I ]> Enter choice: ");
	int n = 0;
	scanf("%d", &n);
	return n;
}

int setupAttr() {
	printf("\n\t\t. . .\n\n");
	printf("\t[ O ]> Confirmed!\n\n");
	printf("\t[ O ]> Select which attractor you would like to simulate:\n\n");
	printf("\t[ O ]> 1: Lorenz,  2: Halvorsen (unstable),  3: Aizawa,  4: Four Wing (unstable),  5: Dadras (unstable),\n");
	printf("\t\t 6: Zhou Chen,  7: Thomas,  8: Rayleigh Bernard,  9: 3-Cells CNN,  10: Release (select to view sub-menu)\n\n");
	printf("\t[ I ]> Enter Choice: ");
	int n = 0;
	scanf("%d", &n);
	if (n==10) {
		printf("\n\n\t[ O ]> Release Attractors, extra attractors added each new release!\n\n");
		printf("\t[ O ]> 1: Ver. 0.0.1 - Bouali.\n");
		printf("\t[ O ]> 2: Ver. 0.0.2 - Chen Lee.\n");
		printf("\t[ O ]> 3: ver. 0.1.0 - Roessler.\n");
		printf("\t[ O ]> 4: ver. 0.1.1 - Gravitational?\n");
		printf("\t[ O ]> 5: ver. 0.1.2 - Sierpinski Differential\n");

		printf("\n\t[ I ]> Enter Choice: ");
		scanf("%d", &n);
		n+=9;
	}
	return n;
}

int setupRT() {
	printf("\n\t\t. . .\n\n");
	printf("\t[ O ]> Confirmed!\n\n");
	printf("\t[ O ]> DEBUG - Would you like to run in static mode?\n");
	printf("\t[ O ]> WARNING - Static mode only renders one node, however said node is simulated MANY times.\n");
	printf("\t[ O ]> It is recommended to only run in static mode with ammount of nodes to simulate set to one, otherwise your computers memory will be eaten up!\n\n");
	printf("\t[ O ]> Run in static mode?\n");
	printf("\t[ O ]> 0: YES, 1: NO\n\n");
	printf("\t[ I ]> Enter choice: ");
	int n = 0;
	scanf("%d", &n);
	return n;
}

void setupConf() {
	printf("\n\t\t. . .\n\n");
	printf("\t[ O ]> Confirmed!\n\n");
	printf("\t[ O ]> To EXIT the simulation, press the ESC key.\n\n");
	printf("\t[ O ]> Press any key and then ENTER to start simulation...\n");
	char temp[256];
	scanf("%s", &temp);
}
