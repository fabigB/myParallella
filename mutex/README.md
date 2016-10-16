# Mutex

This is a small example that runs 16 cores in parallel. They all add 1 to a variable x that is stored in the local address space of the first core: 0x80803500
Each core adds 1 ten times. The suspected result in the end is supposed to be 160 (10x16).

Without the use of mutex the value of that variable would not be 160 but something else. 


It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

