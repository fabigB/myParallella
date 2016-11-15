#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 2
#define ptr_adr_mycore 0x3500
#define ptr_adr_core1  0x80803500
#define ptr_adr_core2  0x80903500

int main(void) {
	char *outbuffer;
	int *myX, *remoteX;
	unsigned timerValStart, timerValStop, time;

	//Set up Barrier
	volatile e_barrier_t bar_array[NUM_CORES]; 
	volatile e_barrier_t *tgt_bar_array[NUM_CORES]; 
    e_barrier_init(bar_array,tgt_bar_array);

	// Set up addresses and set local variable to 0:
	myX = (int *) ptr_adr_mycore;
	remoteX = (int *) ptr_adr_core2;
	*myX = 0;

	// Sync with other core
	e_barrier(bar_array,tgt_bar_array);
	
	//Set up timer:
	timerValStart = e_ctimer_set(E_CTIMER_0,  E_CTIMER_MAX);
	e_ctimer_start(E_CTIMER_0,E_CTIMER_CLK);

	//Write to core 2
	*remoteX = 1;

	//Wait for answer!
	while(*myX != 1);

	//Stop timer:
	timerValStop = e_ctimer_stop(E_CTIMER_0);
	time = timerValStart - timerValStop;
	
    // Write message:
	outbuffer = (char *) 0x3000;
	sprintf(outbuffer, "Clock cycles to send and receive:",time);
    return 0;
}

