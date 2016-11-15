# Comparing communication speed between two cores

This small example project deals with the inter core communication between two cores distributed somewhere on the chip. One core writes to the other core and then awaits a response. A timer is started before the core write to the remote address and stopped after it received an answer. 

The default memory map was assumed (See Figure 10 in Parallella Ref Manual (REV 14.09.09))

--- Work in progress --- 

For each setup 15 runs were performed and the average value was stored

Core0 to Core1: 118 cycles (all the same)

Core0 to Core2: 122,2 cycles (4 * 127 + 7 * 118 + 2 * 127 + 118 + 127)

Core0 to Core3: 123,4 cycles (118 + 127 + 118 + 4 * 127 + 118 + 127 + 118 + 2 * 127 + 2 * 118 + 127)

...

Core0 to Core7:  127 cycles (all the same) 

...

Core0 to CoreC:  124 cycles (2 * 127 + 2 * 118 + 127 + 2 * 118 + 3 * 127 + 118 + 4 * 127)

...

Core0 to CoreF:  132,5 cycles (136 + 2 * 127 + 3 * 136 + 127 + 2 * 136 + 128 + 2* 136 + 128 + 136 + 127)


It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

