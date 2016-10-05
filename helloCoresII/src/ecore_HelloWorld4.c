/*
* Inspired by Copyright (c) 2015, Adam Taylor. All rights reserved.
* Parallella Chronicles Part 3:
* http://adiuvoengineering.com/?page_id=293
*
* Changes by: Fabian Goerge
*/

#include <stdio.h>

#include "e_lib.h"

int *outbuffer;

int main(void) {
        // Variable deceleration for the core id
        e_coreid_t coreid;

        coreid = e_get_coreid();

        // Write message:
        outbuffer = (int*)0x3000;
		*outbuffer = 4;
        return 0;
}

