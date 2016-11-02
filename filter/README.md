# Filter

This is a small example that runs 16 cores in parallel. They all perform the same filter operation on an image. They load one pixle at a time and store it again.

The picture is 352x288 = 101376. 

So each core has to handle: 6336 pixles. 

It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

