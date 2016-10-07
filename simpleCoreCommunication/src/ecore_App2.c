#include <stdio.h>

#include "e_lib.h"

#define ptr_adr_mycore 0x3500
#define ptr_adr_core3  0x80A03500

int main(void) {
		char *outbuffer;
		int *myX;
		int *remoteX;

        // Variable deceleration for the core id
        e_coreid_t coreid;
        coreid = e_get_coreid();

		// Do calculation with x:
		myX = (int *) ptr_adr_mycore;
		*myX = 2;		
		remoteX = (int *) ptr_adr_core3;
		
        // Write message:
		outbuffer = (char *) 0x3000;
		sprintf(outbuffer, "Hello Running App2 from 0x%x my x:%i remote x:%i", coreid, *myX, *remoteX);
        return 0;
}

