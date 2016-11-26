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
runs 1 core. Sets up two timers: one counting clock cycles and the other counting integer ALU instructions. And then outputting the result. 

## interrupt:
runs 1 core. A timer triggers an interrupt.

## mutex:
runs 16 cores all incrementing ten times a shared variable x. The use of mutexes ensures that the increment is done atomic so that the expected result: 160 is produced. 

## filter:
runs 16 cores all doing the same filter operation (inverter / sobel) on a picture and storing it back in memory.

## nocPerformance:
different projects analyzing the Performance of the NoC

A Parallella with a E16G301 epiphany processor was used for all projects.

