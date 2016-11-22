#include <stdio.h>

#include "e-lib.h"

#include "common.h"

bool dmaWait;

void __attribute__((interrupt)) int_isr()
{
	dmaWait = false;
	return;
}	

int main(void) {

	int *remoteX;
	
	remoteX = (int *) ptr_adr_core0;
	
	// Attach the ISR with this interrupt
	e_irq_attach(E_DMA0_INT, int_isr);

	// Clear the IMASK
	e_irq_mask(E_DMA0_INT, E_FALSE);
	
	// Enable the global interrupt
	e_irq_global_mask(E_FALSE);


	do {
		dmaWait = true;
		e_dma_copy((int *) ptr_adr_core6, (int *)0x4000, 1024*sizeof(int));	
		while(dmaWait);	

	}while(remoteX == 0);


    return 0;
}

