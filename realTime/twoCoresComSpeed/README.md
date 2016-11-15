# Core Communication

This small example project deals with the inter core communication between two cores distributed somewhere on the chip. One core writes to the core 2 and then awaits a response.

The default memory map was assumed (See Figure 10 in Parallella Ref Manual (REV 14.09.09))

Core0 to Core1: 127 cycles



It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

