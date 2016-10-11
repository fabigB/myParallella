#include <stdio.h>

#include "e-lib.h"

#define NUM_CORES 4
#define ptr_adr_mycore 0x3200
#define ptr_adr_core1  0x80803500
#define ptr_adr_core2  0x80903500
#define ptr_adr_core3  0x80A03500
#define ptr_adr_core4  0x80B03500

int main(void) {
	char *outbuffer;
	int *myX;
	int i;

	volatile e_barrier_t bar_array[NUM_CORES]; 
	volatile e_barrier_t *tgt_bar_array[NUM_CORES]; 

    e_barrier_init(bar_array,tgt_bar_array);

    // Variable deceleration for the core id
    e_coreid_t coreid;
    coreid = e_get_coreid();

	// Do calculation with x:
	for (i = 0; i < 10; i++)
	{
		myX = (int *) ptr_adr_mycore;
		if 		(coreid == 0x808) *myX = i;
		else if (coreid == 0x809) *myX = i+10;
		else if (coreid == 0x80A) *myX = i+20;
		else 					  *myX = i+30;
		myX += 1;
	}		
	
	// Copy from mycore to different core
	// Size of int: 4 Bytes. * 10
	if 		(coreid == 0x808) e_dma_copy((int *)ptr_adr_core2,(int *)ptr_adr_mycore,40);
	else if (coreid == 0x809) e_dma_copy((int *)ptr_adr_core3,(int *)ptr_adr_mycore,40);
	else if (coreid == 0x80A) e_dma_copy((int *)ptr_adr_core4,(int *)ptr_adr_mycore,40);
	else 					  e_dma_copy((int *)ptr_adr_core1,(int *)ptr_adr_mycore,40);

    // Write message:
	outbuffer = (char *) 0x3000;
	sprintf(outbuffer, "Created 10 elements from 0x%x and used DMA to copy", coreid);
    return 0;
}
