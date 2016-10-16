#include <stdio.h>

#include "e-hal.h"


int main()
{
        /************Variable declaration*************/
        unsigned col, row;
        int intMsg = 999;

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

		// Define a single core work group (size 4x4)
		e_open(&dev,0,0,4,4);
		// Perform soft reset of the created work group
		e_reset_group(&dev);

		for(row=0; row <4; row++)
		{
			for(col=0; col <4; col++)
		    {
				if (row == 0 && col == 0)	feedback = e_load("e_App0.elf",&dev,0,0,E_TRUE);				
				else						feedback = e_load("e_App.elf",&dev,row,col,E_FALSE);
		        if (feedback != E_OK)
		        {
		                fprintf(stderr,"Error (%i) while loading application to core in row: 0 col:%i \n", feedback,col);
		        }
			}
		}
		// Start the group:				
		e_start_group(&dev);
        // Wait for targets to finish:
        usleep(10000);
        
		// Read data of length of the buffer from the work group to local buffer
		e_read(&dev,0,0, 0x3500, &intMsg, sizeof(int));
		fprintf(stderr,"X is supposed to be 16 and it is...%i\n", intMsg);

		// Close work group and free allocated resources. 
        e_close(&dev);
        
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

