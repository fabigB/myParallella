#include <stdio.h>

#include "e-hal.h"

#define FIRSTLINE_SIZE 15
#define PICPART 6336 // 352x288 = 101376 --> /16
#define PIC_START 0x3000

int main()
{
        /************Variable declaration*************/
        unsigned col, row;
		int pixel, counter, firstLines;
		int first;
		char bufFirstLines[FIRSTLINE_SIZE];
		char * line = NULL;
		size_t len = 0;
		int bufInPic[PICPART/2];
		int bufResultPicI[PICPART/2];
		int bufResultPicII[PICPART/2];
		FILE *file;
		size_t nread;
        char message[256];

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
		counter = 0; row = 0; col = 0; firstLines = 0; first = 1;
		if (file) {
			nread = fread(bufFirstLines, 1, sizeof(bufFirstLines), file);
			fprintf(stderr,"Read first Lines:\n%s",bufFirstLines);
		
			while ((nread = getline(&line, &len, file)) != -1) {
				if(line[2] >= '0' && line[2] <= '9')
					pixel = (line[0]-'0') * 100 + (line[1]-'0') * 10 + line[2]-'0'; 
				else if ( line[1] >= '0' && line[1] <= '9')		
					pixel = (line[0]-'0') * 10 + line[1]-'0';		
				else	
					pixel = line[0]-'0';
				bufInPic[counter] = pixel;
				counter += 1;
				if (counter == PICPART/2)	{
					counter = 0;
					//Write to epiphany memory:
					if (first == 1) { 
						e_write(&dev,row,col, PIC_START, &bufInPic, sizeof(bufInPic));
						first = 0; 
					}
					else {
						e_write(&dev,row,col, PIC_START+PICPART/2, &bufInPic, sizeof(bufInPic));
						fprintf(stderr,"Wrote to %i,%i\n",row,col);
						row+=1;
						first = 1;
						if (row == 4) {
							row = 0;
							col+= 1;
						}
					}
					
				}
			}
			fprintf(stderr,"Finished Setup\n");	
			fclose(file);
		}
		
		fprintf(stderr,"Starting groups\n");
		// Start the group:				
		e_start_group(&dev);
        // Wait for targets to finish:
        usleep(10000);
		
		fprintf(stderr,"Reading from groups\n");
		// Read time it took:
		e_read(&dev,0,0, 0x2900, &message, sizeof(message));
        fprintf(stderr,"Core 0 sends: %s\n", message);  
		// Write result:
		file = fopen("../picResult.pgm", "w");
		if (file) {
			fprintf(file, "P2\n");
			fprintf(file, "352 288\n");
			fprintf(file, "255\n");
			for(row=0; row <4; row++) {
				for(col=0; col <4; col++) {			
					// Read data of length of the buffer from the work group to local buffer
					e_read(&dev,row,col, PIC_START, &bufResultPicI, sizeof(bufResultPicI));
					for(counter=0; counter < PICPART/2; counter++) {			
						fprintf(file, "%i\n", bufResultPicI[counter]);
					}
					e_read(&dev,row,col, PIC_START, &bufResultPicII, sizeof(bufResultPicII));
					for(counter=PICPART/2; counter < PICPART; counter++) {			
						fprintf(file, "%i\n", bufResultPicII[counter]);
					}
				}
			}
			fclose(file);
			fprintf(stderr,"Wrote result picture\n");
		}
		else fprintf(stderr,"Failed to open result picture\n");



		// Close work group and free allocated resources. 
        e_close(&dev);
        
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

