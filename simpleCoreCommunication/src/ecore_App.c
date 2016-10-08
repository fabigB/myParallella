#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 4
#define ptr_adr_mycore 0x3500
#define ptr_adr_core1  0x80803500
#define ptr_adr_core2  0x80903500
#define ptr_adr_core3  0x80A03500
#define ptr_adr_core4  0x80B03500

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
	if 		(coreid == 0x808) *myX = 1;
	else if (coreid == 0x809) *myX = 2;
	else if (coreid == 0x80A) *myX = 3;
	else 					  *myX = 4;
		
	e_barrier(bar_array,tgt_bar_array);
	if 		(coreid == 0x808) remoteX = (int *) ptr_adr_core2;
	else if (coreid == 0x809) remoteX = (int *) ptr_adr_core3;
	else if (coreid == 0x80A) remoteX = (int *) ptr_adr_core4;
	else 					  remoteX = (int *) ptr_adr_core1;


    // Write message:
	outbuffer = (char *) 0x3000;
	sprintf(outbuffer, "Hello Running from 0x%x my x:%i remote x:%i", coreid, *myX, *remoteX);
    return 0;
}

