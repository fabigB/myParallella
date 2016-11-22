# Comparing communication latency and bandwith  between two cores using DMA communication 

This small example project deals with the inter core communication between two cores. Core 0 in is placed in the left top most corner and core F is placed in the botom right most corner. Resulting in the longest path. Core 0 writes to the other core using a DMA transfer and then awaits a response. A timer is started before the core write to the remote address and stopped after it received an answer. The DMA can potentialy support 64 Bits per cycle. 

Including the response from F to 0 (22 cycles); Timer: 90 Clock cycles and communication overhead 
| Data (INTS)	| Bits			| Clock cylcles	| 
| ------------- | ------------- | ------------- | 
| 1024			| 32.768		| 2044			| 
| 512			| 16.384		| 1186			| 
| 128			| 4096			| 649			| 
| 2				| 64			| 436			| 

---WORK in progress---




For each setup 100 runs were performed and the average value was stored (Running just the timer takes 89 cycles)
It supposed to take 1.5 clock cycles per hop. 

| From Core0 to | Clock Cycles	| -11,5			| Estimation	|
| ------------- | ------------- | ------------- | ------------- |
| Core1			| 14,5			| 3				| 2*1.5 = 3		|
| Core2			| 15,895		| 4,395			| 3*1.5 = 4,5	|
| Core3			| 17,20			| 5,7			| 4*1.5 = 6		|
| Core4			| 14,58			| 3,08			| 2*1.5 = 3		|
| Core5			| 16,03			| 4,53			| 3*1.5 = 4,5	|
| Core6			| 17,555		| 6,05			| 4*1.5 = 6		|
| Core7			| 19			| 7,5			| 5*1.5 = 7,5	|
| Core8			| 15,85			| 4,35			| 3*1.5 = 4,5	|
| Core9			| 17,29			| 5,79			| 4*1.5 = 6		|
| CoreA			| 19,14			| 7,64			| 5*1.5 = 7,5	|
| CoreB			| 20,12			| 8,62			| 6*1.5 = 9		|
| CoreC			| 17,47			| 5,97			| 4*1.5 = 6		|
| CoreD			| 19,095		| 7,595			| 5*1.5 = 7,5	|
| CoreE			| 20,045		| 8,54			| 6*1.5 = 9		|
| CoreF			| 21,74			| 10,24			| 7*1.5 = 10,5	|


The default memory map was assumed (See Figure 10 in Parallella Ref Manual (REV 14.09.09))

It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

