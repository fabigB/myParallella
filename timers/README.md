# timers

This application shows the use of timers. It runs one core which does the following:

Markup : * set up two timers: one for clock cycles and one for integer ALU instructions
 * starts both timers
 * does some computation for calculating PI
 * performs an evaluation of the timer in between with the get timer function
 * does another PI calculation
 * stops both timers
 * calculates the times
 * writes a message to memory containing the times.

It was tested on a headless parallella desktop board running the (Epiphany toolchain 2016.3.1) 5.2.0

