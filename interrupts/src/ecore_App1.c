#include <stdio.h>

#include "e-lib.h"

/*
* @brief: 	ISR
*/
void __attribute__((interrupt)) endOfTimer_isr() { 
	char *outbuffer;
	outbuffer = (char *) 0x3100;

	//Set an interrupt on the core 0,1 in the workgroup. 		
	e_irq_set(0,1,E_MESSAGE_INT);

	sprintf(outbuffer, "In ISR: Setting interrupt to core 0,1");
			
	return;
}


int main(void) {

	char *outbuffer;

	//attaches the ISR endOfTimer to the interrupt vector table that is specified by E_TIMER0
	e_irq_attach(E_TIMER0_INT, endOfTimer_isr);
	//Interrupts of type E_Timer0 are not masked
	e_irq_mask(E_TIMER0_INT, E_FALSE);
	//Globally enable interrupts on caller core
	e_irq_global_mask(E_FALSE);

	e_ctimer_set(E_CTIMER_0, 50000);
	e_ctimer_start(E_CTIMER_0,E_CTIMER_CLK);

	//Do nothing until the timer reaches 0	
	while(e_ctimer_get(E_CTIMER_0)>0);

	// Write message:
	outbuffer = (char *) 0x3000;
	sprintf(outbuffer, "Done Interrupting");


    return 0;
}

