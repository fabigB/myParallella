#include <stdio.h>

#include "e_lib.h"

#define NUM_CORES 4
#define ptr_adr_mycore 0x3500
#define ptr_adr_core2  0x80903500

int main(void) {
	char *outbuffer;
	int *myX;
	int *remoteX;

	volatile e_barrier_t bar_array[NUM_CORES]; 
	volatile e_barrier_t *tgt_bar_array[NUM_CORES]; 

    e_barrier_init(bar_array,tgt_bar_array);

    // Variable deceleration for the core id
    e_coreid_t coreid;
    coreid = e_get_coreid();

	// Do calculation with x:
	myX = (int *) ptr_adr_mycore;
	*myX = 1;		
	e_barrier(bar_array,tgt_bar_array);
	remoteX = (int *) ptr_adr_core2;

    // Write message:
	outbuffer = (char *) 0x3000;
	sprintf(outbuffer, "Hello Running App1 from 0x%x my x:%i remote x:%i", coreid, *myX, *remoteX);
    return 0;
}

