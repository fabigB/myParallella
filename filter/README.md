# Filter

This is a small example that runs 16 cores in parallel. They all perform the same filter operation on an image. They load one pixel at a time and store it again.

The currently used picture is 128x128 = 16384 /16  

So each core has to handle: 1024 pixels. 

---Still work in progress---
Simple inverter took: aprox 703903


It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

