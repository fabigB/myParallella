#include <stdio.h>

#include "e-hal.h"


int main()
{
        /************Variable declaration*************/
        unsigned col;
        char message[128];
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

		// Define a single core work group (size 1x4)
		e_open(&dev,0,0,1,4);
		// Perform soft reset of the created work group
		e_reset_group(&dev);

		for(col=0; col <4; col++)
        {
    		// Load an Epiphany program HelloWorld onto each of the work group
			// Row and column parameters are relative to work group. Hence 0,0. 
            // Last parameter: E_TRUE is the start parameter and this program will be launched after start 
			feedback = e_load("e_App.elf",&dev,0,col,E_FALSE);
            if (feedback != E_OK)
            {
                    fprintf(stderr,"Error (%i) while loading application to core in row: 0 col:%i \n", feedback,col);
            }
		}
		// Start the group:				
		e_start_group(&dev);
        // Wait for target to finish:
        usleep(1000);
        for(col=0; col <4; col++)
        {	
			// Read data of length of the buffer from the work group to local buffer
            e_read(&dev,0,col,0x3000, &message, 128);
            // Print Result for user to see:
            fprintf(stderr,"Core row: 0, col:%i sends: %s\n", col, message);
    	}
		// Close work group and free allocated resources. 
        e_close(&dev);
        
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

