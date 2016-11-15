#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 2
#define ptr_adr_mycore 0x3500
#define ptr_adr_core1  0x80803500
#define ptr_adr_core2  0x80903500

int main(void) {
	int *myX, *remoteX;
	char *outbuffer;
	outbuffer = (char *) 0x3000;
	
	// Set up addresses and set local variable to 0:
	myX = (int *) ptr_adr_mycore;
	remoteX = (int *) ptr_adr_core1;
	*myX = 0;

	sprintf(outbuffer, "Before While");
	
	//Wait for message from Core 1!
	while(*myX != 1);

	sprintf(outbuffer, "At the end");
	//Write response to Core 1
	*remoteX = 1;

    return 0;
}

