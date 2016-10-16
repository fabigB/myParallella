#include <stdio.h>

#include "e-lib.h"

#define ptr_adr_X  0x80803500


int main(void) {

	int *x;
	x = (int *) ptr_adr_X;
	e_mutex_t    mutex; // group lock mutex

	e_mutex_lock(0,0,&mutex);
	*x = *x+1;
	e_mutex_unlock(0,0,&mutex);

	e_mutex_lock(0,0,&mutex);
	*x = *x+1;
	e_mutex_unlock(0,0,&mutex);

	e_mutex_lock(0,0,&mutex);
	*x = *x+1;
	e_mutex_unlock(0,0,&mutex);

    return 0;
}

