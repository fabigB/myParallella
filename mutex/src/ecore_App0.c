#include <stdio.h>

#include "e-lib.h"

#define ptr_adr_X  0x80803500
#define mutex_adr  0x00004000


int main(void) {

	int *x;
	x = (int *) ptr_adr_X;
	e_mutex_t *mutex;
	mutex = (void *)mutex_adr;

	*x=0;		
	e_mutex_init(0,0,mutex,MUTEXATTR_NULL);

	e_mutex_lock(0,0,mutex);
	x = (int *) ptr_adr_X;	
	*x = *x+1;
	e_mutex_unlock(0,0,mutex);

	e_mutex_lock(0,0,mutex);
	x = (int *) ptr_adr_X;	
	*x = *x+1;
	e_mutex_unlock(0,0,mutex);

	e_mutex_lock(0,0,mutex);
	x = (int *) ptr_adr_X;		
	*x = *x+1;
	e_mutex_unlock(0,0,mutex);


    return 0;
}

