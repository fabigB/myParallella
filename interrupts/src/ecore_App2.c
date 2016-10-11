#include <stdio.h>

#include "e-lib.h"

double aproxPI;
int continueCompute;

/*
* @brief: 	ISR
*/
void __attribute__((interrupt)) stop_isr() { 
	char *outbuffer;
	outbuffer = (char *) 0x3000;
	continueCompute = 0;

	sprintf(outbuffer, "In ISR of Core 2. Calculated %0.5f",aproxPI);
			
	return;
}


int main(void) {

	int x = 0;
	int i = 1;

	e_irq_attach(E_MESSAGE_INT, stop_isr);
	//Interrupts of type E_Timer0 are not masked
	e_irq_mask(E_MESSAGE_INT, E_FALSE);
	//Globally enable interrupts on caller core
	e_irq_global_mask(E_FALSE);

	aproxPI = 0;
	continueCompute = 1;

	while(continueCompute)
	{
		if(x % 2 == 0)	aproxPI += 1.0/(double)i;
		else			aproxPI -= 1.0/(double)i;	
		x++;
		i+=2;
	}

    return 0;
}

