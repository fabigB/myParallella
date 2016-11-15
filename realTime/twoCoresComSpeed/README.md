# Comparing communication speed between two cores

This small example project deals with the inter core communication between two cores distributed somewhere on the chip. One core writes to the other core and then awaits a response. A timer is started before the core write to the remote address and stopped after it received an answer. 

The default memory map was assumed (See Figure 10 in Parallella Ref Manual (REV 14.09.09))

--- Work in progress --- 

Core0 to Core1: 126-127 cycles

Core0 to Core2: 126-127 cycles

Core0 to Core3: 126-127 cycles

...

Core0 to Core7: 126-127 cycles

Core0 to CoreF: 126-136 cycles


It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

