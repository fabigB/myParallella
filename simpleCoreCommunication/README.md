# Core Communication

This small example project deals with the inter core communication. There are four cores involved. Core 1 read from core 2 and core 2 reads from core 3 and so on ...
In order to synchronize the e_barrier was used. 

The default memory map was assumed (See Figure 10 in Parallella Ref Manual (REV 14.09.09))


It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

