#include <stdio.h>

#include "e-lib.h"

#include "common.h"

int main(void) {
	int *myX, *remoteX;
	char *outbuffer;

	//Corid:
	e_coreid_t coreid;
    coreid = e_get_coreid();

	outbuffer = (char *) 0x3000;

	// Set up addresses and set local variable to 0:
	myX = (int *) 0x4FFC; //1023*sizeof(int) = FFC hex + 4000;
	remoteX = (int *) ptr_adr_core0;
	*myX = 0;

	sprintf(outbuffer, "Waiting %d from 0x%x",*myX,coreid);
	//Wait for message from Core 0!
	while(*myX == 0);
	sprintf(outbuffer, "Done %d",*myX);

	//Write response to Core 0
	*remoteX = 1;

    return 0;
}

