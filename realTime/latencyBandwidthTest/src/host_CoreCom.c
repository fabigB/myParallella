#include <stdio.h>

#include "e-hal.h"


int main() {
    /************Variable declaration*************/
    unsigned col;
    char message[64];
	int data[1024];
	char appNameBuf[32];
	int i,m=0;
	double average;

    /*********Epiphany var declaration***********/
    // Epiphany platform information:
    e_platform_t    epiphany_config;
    // Core group data:
    e_epiphany_t    dev;
    // Return values: (could be E_OK, E_ERR or E_WARN)
    e_return_stat_t feedback;


	fprintf(stderr,"Creating data data\n");
	/*******Create Data**********/
	for(i = 0; i < sizeof(data)-1; i++) {
		data[i] = i+2;
	}
	fprintf(stderr,"Done with data data\n");
	data[i-1] = 1;
	
	/*********Epiphany set up***********/
    // Initialize the system:       
    e_init(NULL);
    // Reset the system:
    e_reset_system();
    // Get platform specific configuration, number of devices, external memory, ...
    e_get_platform_info(&epiphany_config);

	e_open(&dev,0,0,4,4);
	fprintf(stderr,"Writing to Cores\n");
//		for(i = 0; i < 100; i++) {        		
		// Perform soft reset of the created work group
		e_reset_group(&dev);

  		// Load the two epiphany programs
		feedback = e_load("e_App_2.elf",&dev,3,3,E_TRUE);
	    if (feedback != E_OK)
	    {
	            fprintf(stderr,"Error (%i) while loading application to core in row: 0 col:1 \n", feedback);
	    }
		usleep(100);
		e_write(&dev,0,0,0x4000, &data, sizeof(data));		
		feedback = e_load("e_App_1.elf",&dev,0,0,E_TRUE);
	    if (feedback != E_OK)
	    {
	            fprintf(stderr,"Error (%i) while loading application to core in row: 0 col:0 \n", feedback);
	    }

	    // Wait for target to finish:
	    usleep(1000);
		// Read data of length of the buffer from the work group to local buffer
	    e_read(&dev,0,0,0x3000, &message, 64);
	    fprintf(stderr, "Result: %s\n", message);
		sscanf(message, "%d", &m);
		average += m;
//	}
		// Close work group and free allocated resources. 
	    e_close(&dev);
	    
	    // release resources allocated by e_init        
	    e_finalize();

//		average = average/i;
//		printf("Average: %f\n",(average-89)/2 );

    return 0;
}

