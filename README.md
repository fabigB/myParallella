# myParallella

This repository holds my Parallella experiment projects.

There are the following projects in the repository:

## helloCores: 
runs one core after another each printing a short Hello message

## helloCoresII: 
runs 4 x four cores in parallel each writing a different message

## simpleCoreCommunication: 
runs 4 cores. Each write a number to a local variable with the help of the barrier() they synchronize and then read a variable from another core using pointers

## DMAcoreCommunication:
runs 4 cores. Each creating a number of local integers first and then writing them to a different core using the DMA copy function.

## timers:
runs 1 core. Sets up two timers: one counting clock cycles and the other counting FPU instructions. And then outputting the result. 

