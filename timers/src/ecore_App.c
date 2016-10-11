#include <stdio.h>

#include "e-lib.h"

/*
* @brief: 	this function uses the Leibniz’ formula to compute pi. 
*			It finishes after n terms of the infinite summation	
*/
double pi(int n)
{
	double result = 0;
	int x = 0;
	int nbrOfTerms = 2*n;
	int i;
	
	for (i = 1; i<nbrOfTerms; i+=2)
	{
		if(x % 2 == 0)	result += 1.0/(double)i;
		else			result -= 1.0/(double)i;	
		x++;
	}

	return result*4.0;
}

int main(void) {

	unsigned timerVal0Start, timerVal0Interval, timerVal0Stop;
	unsigned timer0Pi1, timer0Pi2;
	unsigned timerVal1Start, timerVal1Interval, timerVal1Stop;
	unsigned timer1Pi1, timer1Pi2; 

	double pi1,pi2;

	char *outbuffer;

	// Set up both available timers: (ctimer_id (either 0 or 1) and start value)
	timerVal0Start = e_ctimer_set(E_CTIMER_0,  E_CTIMER_MAX);
	timerVal1Start = e_ctimer_set(E_CTIMER_1,  E_CTIMER_MAX);

	// Start timer:
	//timer 0 counts clock ticks
	e_ctimer_start(E_CTIMER_0,E_CTIMER_CLK);		
	//timer 1 counts integer ALU instructions
	e_ctimer_start(E_CTIMER_1,E_CTIMER_IALU_INST);	

	// Do some computation
	pi1 = pi(5);

	// Get timer:
	timerVal0Interval = e_ctimer_get(E_CTIMER_0);
	timerVal1Interval = e_ctimer_get(E_CTIMER_1);

	// Do some more computation
	pi2 = pi(50);

	// Stop timer:
	timerVal0Stop = e_ctimer_stop(E_CTIMER_0);
	timerVal1Stop = e_ctimer_stop(E_CTIMER_1);

	// Calculate times:
	timer0Pi1 = timerVal0Start - timerVal0Interval;
	timer0Pi2 = timerVal0Interval - timerVal0Stop;
	
	timer1Pi1 = timerVal1Start - timerVal1Interval;
	timer1Pi2 = timerVal1Interval - timerVal1Stop;	

    // Write message:
	outbuffer = (char *) 0x3000;
	sprintf(outbuffer, "Calculated pi1: %0.5f in %u clock cylces and used %u IALU instructions",
			pi1, timer0Pi1, timer1Pi1);

	outbuffer = (char *) 0x3100;
	sprintf(outbuffer, "Calculated pi2: %0.5f in %u clock cylces and used %u IALU instructions", 
			pi2, timer0Pi2, timer1Pi2);

    return 0;
}

