#include <stdio.h>

#include "e-lib.h"

#include "common.h"


int main(void) {
	char *outbuffer;
	int *myX;
	unsigned timerValStart, timerValStop, time;

    // Variable deceleration for the core id
    e_coreid_t coreid;
    coreid = e_get_coreid();

	volatile e_barrier_t bar_array[NUM_CORES]; 
	volatile e_barrier_t *tgt_bar_array[NUM_CORES]; 
    e_barrier_init(bar_array,tgt_bar_array);

	
	outbuffer = (char *) 0x3000;

	// Set up addresses and set local variable to 0:
	myX = (int *) ptr_adr_mycore;
	*myX = 0;

	e_barrier(bar_array,tgt_bar_array);

	//Set up timer:
	timerValStart = e_ctimer_set(E_CTIMER_0,  E_CTIMER_MAX);
	e_ctimer_start(E_CTIMER_0,E_CTIMER_CLK);

	//Write to core F using the DMA (dst,src,bytes)
	if (coreid == 0x808) //Core 0
		e_dma_copy((int *) ptr_adr_coreF, (int *)0x4000, DATA_SIZE*sizeof(int));
	else if (coreid == 0x809) {//Core 2
		e_dma_copy((int *) ptr_adr_core5, (int *)0x4000, 1024*sizeof(int));
		e_dma_copy((int *) ptr_adr_core9, (int *)0x4000, 1024*sizeof(int));
		e_dma_copy((int *) ptr_adr_coreD, (int *)0x4000, 1024*sizeof(int));
	}
	
	//Wait for answer!
	while(*myX == 0);

	//Stop timer:
	timerValStop = e_ctimer_stop(E_CTIMER_0);
	time = timerValStart - timerValStop;
	
    // Write message:
	sprintf(outbuffer, "%u",time);
    return 0;
}

