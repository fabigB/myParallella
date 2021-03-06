#include <stdio.h>

#include "e-hal.h"

#define DATA_SIZE 1024

int main() {
    /************Variable declaration*************/
    unsigned col;
    char message[64];
	int data0[DATA_SIZE];
  int data1[DATA_SIZE];
	int data2[DATA_SIZE];
  int data3[DATA_SIZE];
	char appNameBuf[32];
	int i,m=0;
	double average;

    /*********Epiphany var declaration***********/
    // Epiphany platform information:
    e_platform_t    epiphany_config;
    // Core group data:
    e_epiphany_t    dev1;
    e_epiphany_t    dev2;
    // Return values: (could be E_OK, E_ERR or E_WARN)
    e_return_stat_t feedback;


	/*******Create Data**********/
	for(i = 0; i < DATA_SIZE; i++) {
		data0[i] = i+2;
    data1[i] = i*2;
		data2[i] = 1234+i;
    data3[i] = i%147;
	}
	data0[i-1] = 1;

	/*********Epiphany set up***********/
    // Initialize the system:
    e_init(NULL);
    // Reset the system:
    e_reset_system();
    // Get platform specific configuration, number of devices, external memory, ...
    e_get_platform_info(&epiphany_config);

	e_open(&dev1,0,0,1,4);
	e_open(&dev2,3,3,1,1);
	fprintf(stderr,"Writing to Cores\n");
		for(i = 0; i < 50; i++) {
		// Perform soft reset of the created work group
		e_reset_group(&dev1);
		e_reset_group(&dev2);

  		// Load the two epiphany programs
		feedback = e_load("e_App_2.elf",&dev2,0,0,E_TRUE);
	    if (feedback != E_OK)
	    {
	            fprintf(stderr,"Error (%i) while loading application 2 to core in row: 3 col:3 \n", feedback);
	    }
		usleep(100);
		feedback = e_load("e_App_1.elf",&dev1,0,0,E_FALSE);
	    if (feedback != E_OK)
	    {
	            fprintf(stderr,"Error (%i) while loading application 1 to core in row: 0 col:0 \n", feedback);
	    }
		feedback = e_load("e_App_1.elf",&dev1,0,1,E_FALSE);
	    if (feedback != E_OK)
	    {
	            fprintf(stderr,"Error (%i) while loading application 1 to core in row: 0 col:1 \n", feedback);
	    }
      feedback = e_load("e_App_1.elf",&dev1,0,2,E_FALSE);
  	  if (feedback != E_OK)
  	  {
  	            fprintf(stderr,"Error (%i) while loading application 1 to core in row: 0 col:1 \n", feedback);
  	  }
      feedback = e_load("e_App_1.elf",&dev1,0,3,E_FALSE);
      if (feedback != E_OK)
      {
                fprintf(stderr,"Error (%i) while loading application 1 to core in row: 0 col:1 \n", feedback);
      }

		e_write(&dev1,0,0,0x4000, &data0, sizeof(data0));
		e_write(&dev1,0,1,0x4000, &data1, sizeof(data1));
    e_write(&dev1,0,2,0x4000, &data2, sizeof(data2));
    e_write(&dev1,0,3,0x4000, &data3, sizeof(data3));
		e_start_group(&dev1);


	    // Wait for target to finish:
	    usleep(100000);
		// Read data of length of the buffer from the work group to local buffer
	    e_read(&dev1,0,0,0x3000, &message, 64);
	    fprintf(stderr, "Result: %s\n", message);

		sscanf(message, "%d", &m);
		average += m;
	}
		// Close work group and free allocated resources.
	    e_close(&dev1);
 		e_close(&dev2);

	    // release resources allocated by e_init
	    e_finalize();

		average = average/i;
		printf("Average: %f\n",average );

    return 0;
}
