# DMA Core Communication

This small example project deals with the inter core communication using the DMA functions. There are four cores involved. Each core creates 10 integers and then uses the dma_copy function to copy the data to a different core. Core 1 copies data to core 2 and core 2 copies data to core 3 and so on. In the end each core writes a short message to its local memory (0x3000). The host first reads short message and then the 10 integers that have been copied into that core. 

The default memory map was assumed (See Figure 10 in Parallella Ref Manual (REV 14.09.09))


It was tested on a headless parallella desktop board running the (Epiphany toolchain 2016.3.1) 5.2.0

