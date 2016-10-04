/*
 Inspired by Copyright (c) 2015, Adam Taylor. All rights reserved.
 Parallella Chronicles Part 3:
 http://adiuvoengineering.com/?page_id=293

 Changes by: Fabian Goerge
*/
#include <stdio.h>

#include "e-hal.h"

#define BUFFERSIZE   (128)
#define BUFFEROFFSET (0x01000000)

int main()
{
        /************Variable declaration*************/
        unsigned row, col;
        char message[BUFFERSIZE];

        /*********Epiphany var declaration***********/
        // Epiphany platform information:
        e_platform_t    epiphany_config;
        // Core group data:
        e_epiphany_t    dev;
        // external memory buffer data:
        e_mem_t                 mBuf;
        // Return values: (could be E_OK, E_ERR or E_WARN)
        e_return_stat_t feedback;


        /*********Epiphany set up***********/
        // Initialize the system:       
        e_init(NULL);
        // Reset the system:
        e_reset_system();
        // Get platform specific configuration, number of devices, external memory, ...
        e_get_platform_info(&epiphany_config);
        // Allocate shared memory:
		e_alloc(&mBuf, BUFFEROFFSET, BUFFERSIZE);

        for(row=0; row <4; row++)
		{
			for(col=0; col <4; col++)
            {
                // Addressing each core at a time:

                // Define a single core work group (size 1x1)
                e_open(&dev,row,col,1,1);
                // Perform soft reset of the created work group
                e_reset_group(&dev);
        		// Load an Epiphany program HelloWorld onto the work group
				// Row and column parameters are relative to work group. Hence 0,0. 
                // Last parameter: E_TRUE is the start parameter and this program will be launched after start 
		        feedback = e_load("e_helloWorld.elf",&dev,0,0,E_TRUE);
                if (feedback != E_OK)
                {
                        fprintf(stderr,"Error (%i) while loading application to core in row:%i col:%i \n", feedback,row,col);
                }
                // Wait for target to finish:
                usleep(1000);
                // Read data of length BUFFERSIZE from the work group to local buffer
                e_read(&mBuf,0,0,0x0, message, BUFFERSIZE);
                // Print Result for user to see:
                fprintf(stderr,"Core row:%i, col %i sends: %s\n", row, col, message);
                // Close work group and free allocated resources. 
                e_close(&dev);
        	}
        }
        // release resources allocated by e_alloc 
        e_free(&mBuf);
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

