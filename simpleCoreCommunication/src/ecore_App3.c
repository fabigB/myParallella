#include <stdio.h>

#include "e_lib.h"

char *outbuffer;
int *x;

#define ptr_adr_core4 0x80B01000


int main(void) {
        // Variable deceleration for the core id
        e_coreid_t coreid;
        coreid = e_get_coreid();

		// Do calculation with x:
		x = (int *) ptr_adr_core4;
		x = x+3;

        // Write message:
		outbuffer = (char *) 0x3000;
		sprintf(outbuffer, "Hello Running App3 from 0x%x my x is: %i", coreid, x);
        return 0;
}
