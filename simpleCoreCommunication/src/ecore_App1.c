#include <stdio.h>

#include "e_lib.h"

char *outbuffer;
int *x;

#define ptr_adr_core2 0x80901000


int main(void) {
        // Variable deceleration for the core id
        e_coreid_t coreid;
        coreid = e_get_coreid();

		// Do calculation with x:
		x = (int *) ptr_adr_core2;
		x = x+1;

        // Write message:
		outbuffer = (char *) 0x3000;
		sprintf(outbuffer, "Hello Running App1 from 0x%x my x is: %i", coreid, x);
        return 0;
}

