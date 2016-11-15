#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 2
#define ptr_adr_mycore 0x3500
#define ptr_adr_core1  0x80803500
#define ptr_adr_core2  0x80903500

int main(void) {
	int *myX, *remoteX;
	
	//Set up Barrier
	volatile e_barrier_t bar_array[NUM_CORES]; 
	volatile e_barrier_t *tgt_bar_array[NUM_CORES]; 
    e_barrier_init(bar_array,tgt_bar_array);

	// Set up addresses and set local variable to 0:
	myX = (int *) ptr_adr_mycore;
	remoteX = (int *) ptr_adr_core1;
	*myX = 0;

	// Sync with other core
	e_barrier(bar_array,tgt_bar_array);
	
	//Wait for message from Core 1!
	while(*myX != 1);

	//Write response to Core 1
	*remoteX = 1;

    return 0;
}

