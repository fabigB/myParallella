#include <stdio.h>

#include "e_lib.h"

char *outbuffer;
int *x;

#define ptr_adr_core3 0x80A01000


int main(void) {
        // Variable deceleration for the core id
        e_coreid_t coreid;
        coreid = e_get_coreid();

		// Do calculation with x:
		x = (int *) ptr_adr_core3;
		x = x+2;

        // Write message:
		outbuffer = (char *) 0x3000;
		sprintf(outbuffer, "Hello Running App2 from 0x%x my x is: %i", coreid, x);
        return 0;
}
