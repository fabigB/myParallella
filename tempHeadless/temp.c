/*
Code Taken from:  Adapteva, Inc.
https://github.com/parallella/parallella-utils/blob/master/xtemp/xtemp.c

In the following you see the orgininal copyright notice, a list of conditions and the disclaimer */

/*
Copyright (c) 2014, Adapteva, Inc.
Contributed by Fred Huettig <Fred@Adapteva.com>
All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
  Neither the name of the copyright holders nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>


#define kSTRMAX    256
#define kXADCPATH  "/sys/bus/iio/devices/iio:device0/"

int     nOffset = 0;
float	fScale = 0.0;

int GetConstants() {
	char  strRead[kSTRMAX];
	FILE *sysfile;

	if((sysfile = fopen(kXADCPATH "in_temp0_offset", "ra")) == NULL) {
		fprintf(stderr, "ERROR: Can't open offset device file\n");
		return 1;
	}
	fgets(strRead, kSTRMAX-1, sysfile);
	fclose(sysfile);
	nOffset = atoi(strRead);

	if((sysfile = fopen(kXADCPATH "in_temp0_scale", "ra")) == NULL) {
		fprintf(stderr, "ERROR: Can't open scale device file\n");
		return 2;
		}
	fgets(strRead, kSTRMAX-1, sysfile);
	fclose(sysfile);
	fScale = atof(strRead);

	return 0;
}

int GetTemp(float *fTemp) {
	FILE *sysfile;
	char  strRead[kSTRMAX];
	int  nRaw;

	if(nOffset == 0 || fScale == 0.0)    return 1;

	if((sysfile = fopen(kXADCPATH "in_temp0_raw", "ra")) == NULL) {
		return 2;
	}

	fgets(strRead, kSTRMAX-1, sysfile);
	fclose(sysfile);
	nRaw = atoi(strRead);

	*fTemp = (nRaw + nOffset) * fScale / 1000.;

	return 0;
}

int main()
{

	GetConstants();
	float fTemp;
  	GetTemp(&fTemp);
	printf("Current Temp = %.1f\n", fTemp);
	return 0;
}

