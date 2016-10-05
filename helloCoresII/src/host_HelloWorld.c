/*
 Inspired by Copyright (c) 2015, Adam Taylor. All rights reserved.
 Parallella Chronicles Part 3:
 http://adiuvoengineering.com/?page_id=293

 Changes by: Fabian Goerge
*/
#include <stdio.h>

#include "e-hal.h"

#define BUFFEROFFSET (0x01000000)

int main()
{
        /************Variable declaration*************/
        unsigned row, col;
        int message;
		char appNameBuf[32];

        /*********Epiphany var declaration***********/
        // Epiphany platform information:
        e_platform_t    epiphany_config;
        // Core group data:
        e_epiphany_t    dev;
        // Return values: (could be E_OK, E_ERR or E_WARN)
        e_return_stat_t feedback;

        /*********Epiphany set up***********/
        // Initialize the system:       
        e_init(NULL);
        // Reset the system:
        e_reset_system();
        // Get platform specific configuration, number of devices, external memory, ...
        e_get_platform_info(&epiphany_config);

        for(row=0; row <4; row++)
		{
			// Define a single core work group (size 1x4)
			e_open(&dev,row,0,1,4);
			// Perform soft reset of the created work group
			e_reset_group(&dev);

			for(col=0; col <4; col++)
            {
        		// Load an Epiphany program HelloWorld onto each of the work group
				// Row and column parameters are relative to work group. Hence 0,0. 
                // Last parameter: E_TRUE is the start parameter and this program will be launched after start 
				snprintf(appNameBuf, sizeof(appNameBuf), "e_helloWorld%i.elf", col+1);		        
				feedback = e_load(appNameBuf,&dev,0,col,E_FALSE);
                if (feedback != E_OK)
                {
                        fprintf(stderr,"Error (%i) while loading application to core in row:%i col:%i \n", feedback,row,col);
                }
			}
			// Start the group:				
			e_start_group(&dev);
            // Wait for target to finish:
            usleep(1000);
            for(col=0; col <4; col++)
            {	
				// Read data of length of the buffer from the work group to local buffer
                e_read(&dev,0,col,0x3000, &message, sizeof(int));
                // Print Result for user to see:
                fprintf(stderr,"Core row:%i, col:%i sends: %i\n", row, col, message);
                // Close work group and free allocated resources. 
                e_close(&dev);
        	}
        }
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

