#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 16
#define PICPART 6336 // 352x288 = 101376 --> /16
#define PIC_START 0x3000

int main(void) {

	int *x;
	int i;
	char *outbuffer;
	unsigned timerVal0Start, timerVal0Stop;
    e_coreid_t coreid;
    
	//Get CoreID
	coreid = e_get_coreid();
	if (coreid == 0x808) {
		//Timer Init:
		// Set up timer: (ctimer_id and start value)
		timerVal0Start = e_ctimer_set(E_CTIMER_0,  E_CTIMER_MAX);
		// Start timer:
		//timer 0 counts clock ticks
		e_ctimer_start(E_CTIMER_0,E_CTIMER_CLK);		
	}

	//Barrier Init:
	volatile e_barrier_t bar_array[NUM_CORES]; 
	volatile e_barrier_t *tgt_bar_array[NUM_CORES]; 
    e_barrier_init(bar_array,tgt_bar_array);

	//Simply invert
	for ( i = 0; i < PICPART; i++) {
		x = (int *) PIC_START + i;
		*x = 255-*x;
	}

	//Meet all at the barrier
	e_barrier(bar_array,tgt_bar_array);

	if (coreid == 0x808) {
		// Stop timer:
		timerVal0Stop = e_ctimer_stop(E_CTIMER_0);
		outbuffer = (char *) 0x4900;
		sprintf(outbuffer, "Filter done in %u clock cylces",timerVal0Stop);
	}

    return 0;
}

