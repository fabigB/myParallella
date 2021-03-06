#include <stdio.h>

#include "e-lib.h"

#include "common.h"

int main(void) {
	int *myX, *remoteX;

	// Set up addresses and set local variable to 0:
	myX = (int *) 0x4FFC; //1023*sizeof(int) = FFC hex + 4000;
	remoteX = (int *) ptr_adr_core0;
	*myX = 0;

	//Wait for message from Core 0!
	while(*myX == 0);

	//Write response to Core 0
	*remoteX = 1;

    return 0;
}
