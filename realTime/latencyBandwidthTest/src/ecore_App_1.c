#include <stdio.h>

#include "e-lib.h"

#include "common.h"


int main(void) {
	char *outbuffer;
	int *myX, *myTemp;
	unsigned timerValStart, timerValStop, time;

	outbuffer = (char *) 0x3000;

	// Set up addresses and set local variable to 0:
	myX = (int *) ptr_adr_mycore;
	*myX = 0;

	myTemp = (int *) 0x4FFC;
	sprintf(outbuffer, "1 = %d",*myTemp);
	//Set up timer:
	timerValStart = e_ctimer_set(E_CTIMER_0,  E_CTIMER_MAX);
	e_ctimer_start(E_CTIMER_0,E_CTIMER_CLK);

	//Write to core F using the DMA (dst,src,bytes)
	e_dma_copy((int *)0x8cb04000,(int *)0x4000,1024*sizeof(int));

	//Wait for answer!
	while(*myX == 0);

	//Stop timer:
	timerValStop = e_ctimer_stop(E_CTIMER_0);
	time = timerValStart - timerValStop;
	
    // Write message:
	sprintf(outbuffer, "%u",time);
    return 0;
}

