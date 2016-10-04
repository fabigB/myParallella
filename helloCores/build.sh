#!/bin/bash

set -e

ELIBS=${EPIPHANY_HOME}/tools/host/lib
EINCS=${EPIPHANY_HOME}/tools/host/include
ELDF=${EPIPHANY_HOME}/bsps/current/fast.ldf

if [[ $(uname -p) == *"arm"* ]]; then
	CROSS_PREFIX=
else	
	CROSS_PREFIX="arm-linux-gnueabihf-"
fi

# Build HOST side application
${CROSS_PREFIX}gcc src/host_HelloWorld.c -o debug/helloWorld.elf -I ${EINCS} -L ${ELIBS} -le-hal -le-loader

# Build DEVICE side program
e-gcc -T ${ELDF} src/ecore_HelloWorld.c -o debug/e_helloWorld.elf -le-lib

# Convert ebinary to SREC file
e-objcopy --srec-forceS3 --output-target srec debug/e_helloWorld.elf debug/helloWorld.srec

