#!/bin/bash

set -e

ELIBS=${EPIPHANY_HOME}/tools/host/lib:${LD_LIBRARY_PATH}

cd debug

sudo -E LD_LIBRARY_PATH=${ELIBS} EPIPHANY_HDF=${EPIPHANY_HDF} ./hostTimer.elf
