#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 16
#define PICPART 1024 //128x128 --> 16384 /16 = 1024 
#define ROW_LENGTH 128
#define PIC_START 0x8f000000

//Using shared_dram:  0x8f000000 - 0x8f7fffff Size: 0x00800000 (8 MB)

int abs(int x) {
	if (x < 0) return -x;
	else return x;
}


int main(void) {

	int *x;
	int i;
	int offset = 0;
	char *outbuffer;
	unsigned timerVal0Start, timerVal0Stop;
    e_coreid_t coreid;
	int *u0, *u1, *u2, *m0, *m1, *m2, *l0, *l1, *l2;
	int s1, s2, sobel;
    
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

/*	//Simply invert
	for ( i = 0; i < PICPART; i++) {
		x = (int *) PIC_START+ PICPART*offset + i;
		*x = 255-*x;
	}
*/

	//Simple Sobel - Reading every pixel 9 times
	for ( i = 0; i < PICPART; i++) {
		u0 = (int *) PIC_START+ PICPART*offset + i - ROW_LENGTH - 1;
		u1 = (int *) PIC_START+ PICPART*offset + i - ROW_LENGTH;
		u2 = (int *) PIC_START+ PICPART*offset + i - ROW_LENGTH + 1;
		m0 = (int *) PIC_START+ PICPART*offset + i - 1;
		m1 = (int *) PIC_START+ PICPART*offset + i;
		m2 = (int *) PIC_START+ PICPART*offset + i + 1;
		l0 = (int *) PIC_START+ PICPART*offset + i + ROW_LENGTH - 1;
		l1 = (int *) PIC_START+ PICPART*offset + i + ROW_LENGTH;
		l2 = (int *) PIC_START+ PICPART*offset + i + ROW_LENGTH + 1;
		if (coreid == 0x808) {
			//First row - mirror first row
			u0 = m0;
			u1 = m1;
			u2 = m2;
		}
		else if (coreid == 0x8cb) {
			//Last row - mirror last row
			l0 = m0;
			l1 = m1;
			l2 = m2;
		}
		if (i == 0) {
			//First pixel in each row
			u0 = u1;
			m0 = m1;			
			l0 = l1;
		}
		else if (i == (ROW_LENGTH-1)) {
			//Last pixel in each row
			u2 = u1;
			m2 = m1;
			l2 = l1;
		}
		s1 = abs( *u0 - *l0 + (*u1)*2 - (*l1)*2 + *u2 - *l2);
		s2 = abs( *u2 - *u0 + (*m2)*2 - (*m0)*2 + *l2 - *l0);
		sobel = ( s1 + s2 ) / 8;
		*m1 = sobel;
		
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

