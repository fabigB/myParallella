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
${CROSS_PREFIX}gcc src/host_HelloWorld.c -o debug/helloWorld.elf -I ${EINCS} -L ${ELIBS} -le-hal -le-loader

# Build DEVICE side program
e-gcc -T ${ELDF} src/ecore_HelloWorld1.c -o debug/e_helloWorld1.elf -le-lib
e-gcc -T ${ELDF} src/ecore_HelloWorld2.c -o debug/e_helloWorld2.elf -le-lib
e-gcc -T ${ELDF} src/ecore_HelloWorld3.c -o debug/e_helloWorld3.elf -le-lib
e-gcc -T ${ELDF} src/ecore_HelloWorld4.c -o debug/e_helloWorld4.elf -le-lib
