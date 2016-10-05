/*
* Inspired by Copyright (c) 2015, Adam Taylor. All rights reserved.
* Parallella Chronicles Part 3:
* http://adiuvoengineering.com/?page_id=293
*
* Changes by: Fabian Goerge
*/

#include <stdio.h>

#include "e_lib.h"

char outbuffer[128] SECTION("shared_dram");

int main(void) {
        // Variable deceleration for the core id
        e_coreid_t coreid;

        coreid = e_get_coreid();

        // Write message:
        sprintf(outbuffer, "Hello Running App4 from 0x%x", coreid);
        return 0;
}

