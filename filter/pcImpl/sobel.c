#include <stdio.h>
#include <time.h>

#define ROW_LENGTH 128
#define FIRSTLINE_SIZE 15
#include <stdint.h>

int abs(int x) {
	if (x < 0) return -x;
	else return x;
}

//Taken from here: http://stackoverflow.com/questions/459691/best-timing-method-in-c
inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ (
      "xorl %%eax, %%eax\n"
      "cpuid\n"
      "rdtsc\n"
      : "=a" (lo), "=d" (hi)
      :
      : "%ebx", "%ecx");
    return (uint64_t)hi << 32 | lo;
}


int main(void) {

	int i, j;
	int s1, s2, result;
	int line1[ROW_LENGTH],line2[ROW_LENGTH], line3[ROW_LENGTH];
	int lineCounter, rowCounter;

	FILE *file, *fileResult;
	char bufFirstLines[FIRSTLINE_SIZE];
	char * line = NULL;
	size_t len = 0;
	size_t nread;
	int pixel;
    
	unsigned long long x,y;


	// Start timer:
	x = rdtsc();

	file = fopen("picIn.pgm", "r");
	fileResult = fopen("picResult.pgm", "w");
	//Fast Sobel - Reading every pixel once
	rowCounter = 0;
	lineCounter = 0;
	i = 0;

	if (file) {
		//First lines include special information:			
		nread = fread(bufFirstLines, 1, sizeof(bufFirstLines), file);
		fprintf(fileResult, "%s", bufFirstLines);
		//Read pixels:
		while ((nread = getline(&line, &len, file)) != -1) {
			if(line[2] >= '0' && line[2] <= '9')
				pixel = (line[0]-'0') * 100 + (line[1]-'0') * 10 + line[2]-'0'; 
			else if ( line[1] >= '0' && line[1] <= '9')		
				pixel = (line[0]-'0') * 10 + line[1]-'0';		
			else	
				pixel = line[0]-'0';

			if ( i < ROW_LENGTH ) {
				//First row:
				line1[i] = pixel;
				line2[i] = pixel;
			}
			else if ( i < (2*ROW_LENGTH) ) {
				//Second row:
				line3[lineCounter] = pixel;
				lineCounter++;
			}
			else {		
				//Shift old values:
				line1[lineCounter] = line2[lineCounter];
				line2[lineCounter] = line3[lineCounter];
				//Load new line:
				line3[lineCounter] = pixel;
				lineCounter++;
			}

			if ( lineCounter==ROW_LENGTH ) {
				// End of a row. Do computation
				//First pixel in each 
				s1 = abs( line1[0] - line3[0] + line1[0]*2 - line3[0]*2 + line1[1] - line3[1]);			
				s2 = abs( line1[1] - line1[0] + line2[1]*2 - line2[0]*2 + line3[1] - line3[0]);
				result = ( s1 + s2 ) / 8;	
				//Write back:
				fprintf(fileResult, "%i\n", result);	
				
				
				//Pixels inbetween			
				for(j = 1; j < ROW_LENGTH-1; j++) {
					s1 = abs( line1[j-1] - line3[j-1] + line1[j]  *2 - line3[j]  *2 + line1[j+1] - line3[j+1]);			
					s2 = abs( line1[j+1] - line1[j-1] + line2[j+1]*2 - line2[j-1]*2 + line3[j+1] - line3[j-1]);
					result = ( s1 + s2 ) / 8;
					//Write back:
					fprintf(fileResult, "%i\n", result);		
				}
				
				//Last pixel in each row
				j = ROW_LENGTH-1;
				s1 = abs( line1[j-1] - line3[j-1] + line1[j]*2 - line3[j]  *2 + line1[j] - line3[j]);			
				s2 = abs( line1[j]   - line1[j-1] + line2[j]*2 - line2[j-1]*2 + line3[j] - line3[j-1]);
				result = ( s1 + s2 ) / 8;
				//Write back:
				fprintf(fileResult, "%i\n", result);	
						
				//Reset the line counter and increment the row. 
				lineCounter = 0;
				rowCounter++;
			}
			i++;		
		}
	}
	fclose(file);
	
	//Quick and dirty last line:
	for(i = 0; i < ROW_LENGTH; i++) {
		line1[i] = line2[i];
		line2[i] = line3[i];
	}	

	//First pixel in each 
	s1 = abs( line1[0] - line3[0] + line1[0]*2 - line3[0]*2 + line1[1] - line3[1]);			
	s2 = abs( line1[1] - line1[0] + line2[1]*2 - line2[0]*2 + line3[1] - line3[0]);
	result = ( s1 + s2 ) / 8;	
	//Write back:
	fprintf(fileResult, "%i\n", result);	
	
	//Pixels inbetween			
	for(j = 1; j < ROW_LENGTH-1; j++) {
		s1 = abs( line1[j-1] - line3[j-1] + line1[j]  *2 - line3[j]  *2 + line1[j+1] - line3[j+1]);			
		s2 = abs( line1[j+1] - line1[j-1] + line2[j+1]*2 - line2[j-1]*2 + line3[j+1] - line3[j-1]);
		result = ( s1 + s2 ) / 8;
		//Write back:
		fprintf(fileResult, "%i\n", result);		
	}
	
	//Last pixel in each row
	j = ROW_LENGTH-1;
	s1 = abs( line1[j-1] - line3[j-1] + line1[j]*2 - line3[j]  *2 + line1[j] - line3[j]);			
	s2 = abs( line1[j]   - line1[j-1] + line2[j]*2 - line2[j-1]*2 + line3[j] - line3[j-1]);
	result = ( s1 + s2 ) / 8;
	//Write back:
	fprintf(fileResult, "%i\n", result);

	// Stop timer:
	y = rdtsc();
	// lscpu | grep "MHz". --> 800 MHz	
	printf("Took: %f s\n",(y-x)*0.000000001);

    return 0;
}

