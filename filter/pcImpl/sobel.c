#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PICSIZE 16384 //262144
#define ROW_LENGTH 128 //512
#define FIRSTLINE_SIZE 15

int abs(int x) {
	if (x < 0) return -x;
	else return x;
}


int main(void) {

	//File Handling
	FILE *file, *fileResult;
	char bufFirstLines[FIRSTLINE_SIZE];
	char * line = NULL;
	size_t len = 0;
	size_t nread;
	int source[PICSIZE], destination[PICSIZE];

	//Algorithm
	int i, j;
	int s1, s2;
	int line1[ROW_LENGTH], line2[ROW_LENGTH], line3[ROW_LENGTH];
	int lineCounter, rowCounter;

    //Timer
	clock_t begin,end;
	double time_spent;


	//Read file into buffer:
	file = fopen("picIn.pgm", "r");
	i = 0;
	if (file) {
		//First lines include special information:			
		nread = fread(bufFirstLines, 1, sizeof(bufFirstLines), file);
		//Read pixels:
		while ((nread = getline(&line, &len, file)) != -1) {
			source[i] = atoi(line);
			i++;
		}
	}
	fclose(file);

	// Start timer:
	begin = clock();

	//Fast Sobel - Reading every pixel once
	rowCounter = 0;
	lineCounter = 0;
	for ( i = 0; i < PICSIZE+ROW_LENGTH; i++) {
		if( i < (2*ROW_LENGTH) ) {
			//Load the first three lines:
			if ( i < ROW_LENGTH ) {
				line2[i] = source[i];
				line1[i] = line2[i]; //The first row will be mirrowed
			}
			else {
				line3[lineCounter] = source[i];
				lineCounter++;
			} 
		}
		else {
			//Shift old values:
			line1[lineCounter] = line2[lineCounter];
			line2[lineCounter] = line3[lineCounter];
			//Load new line:
			if(i < PICSIZE) 	 line3[lineCounter] = source[i];
			lineCounter++;
		}
		if ( lineCounter==ROW_LENGTH ) {
			// End of a row. Do computation
			//First pixel in each 
			s1 = abs( line1[0] - line3[0] + line1[0]*2 - line3[0]*2 + line1[1] - line3[1]);			
			s2 = abs( line1[1] - line1[0] + line2[1]*2 - line2[0]*2 + line3[1] - line3[0]);
			destination[ROW_LENGTH*rowCounter] = ( s1 + s2 ) / 8;	
			//Pixels inbetween			
			for(j = 1; j < ROW_LENGTH-1; j++) {
				s1 = abs( line1[j-1] - line3[j-1] + line1[j]  *2 - line3[j]  *2 + line1[j+1] - line3[j+1]);			
				s2 = abs( line1[j+1] - line1[j-1] + line2[j+1]*2 - line2[j-1]*2 + line3[j+1] - line3[j-1]);
				destination[ROW_LENGTH*rowCounter + j] = ( s1 + s2 ) / 8;	
			}
			//Last pixel in each row
			j = ROW_LENGTH-1;
			s1 = abs( line1[j-1] - line3[j-1] + line1[j]*2 - line3[j]  *2 + line1[j] - line3[j]);			
			s2 = abs( line1[j]   - line1[j-1] + line2[j]*2 - line2[j-1]*2 + line3[j] - line3[j-1]);
			destination[ROW_LENGTH*rowCounter + j] = ( s1 + s2 ) / 8;

			//Reset the line counter and increment. 
			lineCounter = 0;
			rowCounter++;
		}		
	}

	// Stop timer:
	end = clock();

	// Writing file back 
	fileResult = fopen("picResult.pgm", "w");
	if (fileResult) {
		printf("Writing result\n");
		//First lines include special information:			
		fprintf(fileResult, "%s", bufFirstLines);
		//Read pixels:
		for(i = 0; i < PICSIZE; i++) {
			fprintf(fileResult, "%i\n", destination[i]);
		}
	}
	fclose(file);

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Took: %f seconds\n",time_spent);

    return 0;
}

