#include <stdio.h>

#include "e-hal.h"

#define FIRSTLINE_SIZE 15
#define PICSIZE 16384 // 128x128
#define PICPART 1024 //  16384 /16 = 1024

#define BUFFEROFFSET (0x01000000)
//The offset for e_alloc will be an offset from 0x8e000000:
//	Offset of 0x01000000 --> 0x8e000000 + 0x01000000 = 0x8f000000 (shared_dram)
int main()
{
        /************Variable declaration*************/
        unsigned col, row;
		int pixel, counter, firstLines, memOffsetCount;
		int first;
		char bufFirstLines[FIRSTLINE_SIZE];
		char * line = NULL;
		size_t len = 0;
		int bufInPic[PICPART];
		int bufResultPic[PICPART];
		FILE *file;
		size_t nread;
		// Core message:
        char message[32];        
		// external memory buffer data:
        e_mem_t	mBuf;

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


        // Allocate shared memory:
		e_alloc(&mBuf, BUFFEROFFSET, 19456);

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
		counter = 0; row = 0; col = 0; firstLines = 0; first = 1; memOffsetCount = 0;
		if (file) {
			//First lines include special information:			
			nread = fread(bufFirstLines, 1, sizeof(bufFirstLines), file);
			//Read pixels:
			while ((nread = getline(&line, &len, file)) != -1) {
				if(line[2] >= '0' && line[2] <= '9')
					pixel = (line[0]-'0') * 100 + (line[1]-'0') * 10 + line[2]-'0'; 
				else if ( line[1] >= '0' && line[1] <= '9')		
					pixel = (line[0]-'0') * 10 + line[1]-'0';		
				else	
					pixel = line[0]-'0';
				bufInPic[counter] = pixel;
				counter += 1;
				if (counter == PICPART)	{
					counter = 0;
					//Write to epiphany memory:
					e_write(&mBuf,0,0, PICPART*memOffsetCount, &bufInPic, sizeof(bufInPic));
					fprintf(stderr,"Wrote to %i\n",PICPART*memOffsetCount);
					memOffsetCount+=1;						
				}
			}
			fprintf(stderr,"Finished Setup\n");	
			fclose(file);
		}
		
		fprintf(stderr,"Starting groups\n");
		// Start the group:				
		e_start_group(&dev);
        // Wait for targets to finish:
        usleep(100000);
		
		fprintf(stderr,"Reading from groups\n");
		// Write result:
		file = fopen("../picResult.pgm", "w");
		if (file) {
			fprintf(file, "%s", bufFirstLines);
			memOffsetCount = 0;
			for(row=0; row <4; row++) {
				for(col=0; col <4; col++) {			
					// Read data of length of the buffer from the work group to local buffer
					e_read(&mBuf,0,0, PICPART*memOffsetCount, &bufResultPic, sizeof(bufResultPic));
					for(counter=0; counter < PICPART; counter++) {			
						fprintf(file, "%i\n", bufResultPic[counter]);
					}
					memOffsetCount+=1;
				}
			}
			fclose(file);
			fprintf(stderr,"Wrote result picture\n");
		}
		else fprintf(stderr,"Failed to open result picture\n");
		// Read time it took:
		e_read(&dev,0,0, 0x2000, &message, sizeof(message));
        fprintf(stderr,"Core 0 sends:%s\n", message);  


		// Close work group and free allocated resources. 
        e_close(&dev);
        // release resources allocated by e_alloc 
        e_free(&mBuf);
        // release resources allocated by e_init        
        e_finalize();

        return 0;
}

