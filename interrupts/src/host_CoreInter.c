#include <stdio.h>

#include "e-hal.h"


int main()
{
        /************Variable declaration*************/
        char message[128];

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

		// Define a single core work group (size 1x1)
		e_open(&dev,0,0,1,1);
		// Perform soft reset of the created work group
		e_reset_group(&dev);

		// Load an Epiphany program onto the work group
		// Row and column parameters are relative to work group. Hence 0,0. 
		feedback = e_load("e_App1.elf",&dev,0,0,E_FALSE);
        if (feedback != E_OK)
        {
                fprintf(stderr,"Error (%i) while loading application to core. \n", feedback);
        }
		e_start_group(&dev);

        // Wait for target to finish:
        usleep(100000);

        e_read(&dev,0,0,0x3000, &message, 128);   
        fprintf(stderr,"Core 0 sends: %s\n", message);  
        e_read(&dev,0,0,0x3100, &message, 128);   
        fprintf(stderr,"Core 0 sends: %s\n", message);   

		// Close work group and free allocated resources. 
        e_close(&dev);
        
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

