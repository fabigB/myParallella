#include <stdio.h>

#include "e-lib.h"

#define PICPART 6336 // 352x288 = 101376 --> /16
#define PIC_START 0x3500

int main(void) {

	int *x;
	int i;

	//Simply invert
	for ( i = 0; i < PICPART; i++) {
		x = (int *) PIC_START + i;
		*x = 255-*x;
	}


    return 0;
}

