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

mkdir -p debug/
# Build HOST side application
${CROSS_PREFIX}gcc src/host_Mutex.c -o debug/hostMutex.elf -I ${EINCS} -L ${ELIBS} -le-hal -le-loader

# Build DEVICE side program
e-gcc -T ${ELDF} src/ecore_App.c -o debug/e_App.elf -le-lib
e-gcc -T ${ELDF} src/ecore_App0.c -o debug/e_App0.elf -le-lib
