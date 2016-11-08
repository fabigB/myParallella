#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 16
#define PICPART 4096 // 256x256 = 65536 --> /16 = 4096
#define PIC_START 0x8f000000

//Using shared_dram:  0x8f000000 - 0x8f7fffff Size: 0x00800000 (8 MB)

int main(void) {

	int *x;
	int i;
	int offset = 0;
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


	switch(coreid) {
		case 0x808: offset = 0;  break;
		case 0x809: offset = 1;  break;
		case 0x80a: offset = 2;  break;
		case 0x80b: offset = 3;  break;
		case 0x848: offset = 4;  break;
		case 0x849: offset = 5;  break;
		case 0x84a: offset = 6;  break;
		case 0x84b: offset = 7;  break;
		case 0x888: offset = 8;  break;
		case 0x889: offset = 9;  break;
		case 0x88a: offset = 10; break;
		case 0x88b: offset = 11; break;
		case 0x8c8: offset = 12; break;
		case 0x8c9: offset = 13; break;
		case 0x8ca: offset = 14; break;
		case 0x8cb: offset = 15; break;
		default:	offset = 99; break;
	}

	//Simply invert
	for ( i = 0; i < PICPART; i++) {
		x = (int *) PIC_START+ PICPART*offset + i;
		*x = 255-*x;
	}

	//Meet all at the barrier
	e_barrier(bar_array,tgt_bar_array);


	if (coreid == 0x808) {
		// Stop timer:
		timerVal0Stop = e_ctimer_stop(E_CTIMER_0);
		outbuffer = (char *) 0x2000;
		sprintf(outbuffer, "Done in: %u clk cylces",timerVal0Start-timerVal0Stop);
	}


    return 0;
}

