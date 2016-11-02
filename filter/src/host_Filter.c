#include <stdio.h>

#include "e-hal.h"

#define PIX2 3	//Maximum 255
#define PICPART 6336 // 352x288 = 101376 --> /16

int main()
{
        /************Variable declaration*************/
        unsigned col, row;
		int pixel, counter, firstLines;
		char bufLine[3];
		int bufPic[PICPART];
		FILE *file;
		size_t nread;

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

		for(row=0; row <4; row++) {
			for(col=0; col <4; col++) {
				feedback = e_load("e_App.elf",&dev,row,col,E_FALSE);										
		        if (feedback != E_OK) {
		                fprintf(stderr,"Error (%i) while loading application to core in row: 0 col:%i \n", feedback,col);
		        }
			}
		}
		// Fill the memory:
		file = fopen("../src/picIn.pgm", "r");
		counter = 0; row = 0; col = 0; firstLines = 0;
		if (file) {
			while ((nread = fread(bufLine, 1, sizeof(bufLine), file)) > 0) {
				if(firstLines < 3) {
					//ignore first three lines					
					firstLines++;					
					continue;
				}
				pixel = bufLine[0]-'0' * 1 + bufLine[0]-'0' * 10 + bufLine[0]-'0' * 100;
				bufPic[counter] = pixel;
				counter += 1;
				if (counter == PICPART)	{
					//Write to epiphany memory:
					e_write(&dev,row,col, 0x3500, &bufPic, sizeof(bufPic));
					fprintf(stderr,"Wrote to %i,%i. Last Pixel was:%i in chars: %s", row, col,pixel,bufLine);
					row+=1;
					if (row == 4) {
						row = 0;
						col+= 1;
					}
					counter = 0;
				}
			}
			fclose(file);
		}
		

		// Start the group:				
		e_start_group(&dev);
        // Wait for targets to finish:
        usleep(100000);
		
		// Write result:
		file = fopen("picResult.pgm", "w");
		if (file) {
			fprintf(file, "P2\n");
			fprintf(file, "352 288\n");
			fprintf(file, "255\n");
			for(row=0; row <4; row++) {
				for(col=0; col <4; col++) {			
					// Read data of length of the buffer from the work group to local buffer
					e_read(&dev,row,col, 0x3500, &bufPic, sizeof(bufPic));
					for(counter=0; counter < PICPART; counter++) {			
						fprintf(file, "%i\n", bufPic[counter]);
					}
				}
			}
			fclose(file);
		}



		// Close work group and free allocated resources. 
        e_close(&dev);
        
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

