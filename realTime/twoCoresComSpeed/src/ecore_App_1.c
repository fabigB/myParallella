#include <stdio.h>

#include "e-lib.h"

#include "common.h"

int main(void) {
	char *outbuffer;
	int *myX, *remoteX;
	unsigned timerValStart, timerValStop, time;
	outbuffer = (char *) 0x3000;

	// Set up addresses and set local variable to 0:
	myX = (int *) ptr_adr_mycore;
	remoteX = (int *) ptr_adr_core1;
	*myX = 0;

	//Set up timer:
	timerValStart = e_ctimer_set(E_CTIMER_0,  E_CTIMER_MAX);
	e_ctimer_start(E_CTIMER_0,E_CTIMER_CLK);

	//Write to core 1
	*remoteX = 1;

	//Wait for answer!
	while(*myX != 1);

	//Stop timer:
	timerValStop = e_ctimer_stop(E_CTIMER_0);
	time = timerValStart - timerValStop;
	
    // Write message:
	sprintf(outbuffer, "Clock cycles to send and receive: %u",time);
    return 0;
}

