# Comparing communication latency and bandwith  between two cores using DMA communication 

This small example project deals with the inter core communication between two cores. Core 0 in is placed in the left top most corner and core F is placed in the botom right most corner. Resulting in the longest path. Core 0 writes to the other core using a DMA transfer and then awaits a response. A timer is started before the core write to the remote address and stopped after it received an answer. The DMA can potentialy support 64 Bits per cycle. 

Sending Data from core 0 to F including the response from F to 0 (approx 22 cycles); Timer: 89 Clock cycles and communication overhead 
| Data (INTS)	| Bits			| Clock cylcles	| 
| ------------- | ------------- | ------------- | 
| 1024			| 32.768 (4 kB)	| 2066			| 
| 512			| 16.384 (2 kB)	| 1199			| 
| 128			| 4096 (0,5 kB)	| 657			| 
| 2				| 64			| 443			| 


Sending Data from core 0 to 3 including the response from 3 to 0 (approx 18 cycles); Timer: 89 Clock cycles and communication overhead 
| Data (INTS)	| Bits			| Clock cylcles	| 
| ------------- | ------------- | ------------- | 
| 1024			| 32.768 (4 kB)	| 2066			| 
| 512			| 16.384 (2 kB)	| 1199			| 
| 128			| 4096 (0,5 kB)	| 657			| 
| 2				| 64			| 443			|

Influence of other cores sending data. The initial setup was taken again where core 0 sends data to core F. Adding different DMA copy instructions to see how the speed of the writing of the data can be manipulated:

| Adding				| kB			| Clock cylcles	| 
| --------------------- | ------------- | ------------- | 
| Core 1 sends to Core 0| 4 kB			| approx 2075	| 
| Core 1 to Core 3		| 4 kB			| approx 2075	| 
| 1-7					| 4 kB			| approx 2075	| 
| 1-B					| 4 kB			| approx 2075	| 
| 1-2 & 1-3				| 4 kB			| approx 2061	| 
| 1-2 & 1-3 & 1-7		| 4 kB			| approx 2060	| 
| 1-2 & 1-3 & 1-7 & 1-B | 4 kB			| approx 2075	| 

For each setup 100 runs were performed and the average value was stored 

The default memory map was assumed (See Figure 10 in Parallella Ref Manual (REV 14.09.09))

It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

