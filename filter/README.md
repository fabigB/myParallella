# Filter

This is a small example that runs 16 cores in parallel. They all perform the same filter operation on an image. They load one pixel at a time and store it again.

The currently used picture is 128x128 = 16384 /16  

So each core has to handle: 1024 pixels. Three different implementations where examined. 

| Filter          | Clock Cycles  	|
| --------------- | --------------- |
| Simple inverter |  aprx 703903	|
| Simple sobel    |	 aprx 6095297	|
| Fast sobel 	  |	 aprx 977654	|

For a picture the size 512x512 the following numbers where acquired (16 times bigger):

| Filter          | Clock Cycles  	|
| --------------- | --------------- |
| Simple inverter |  aprx 10957514	|
| Simple sobel    |	 aprx 113780308|
| Fast sobel 	  |	 aprx 14933029	|


If a picture of different size should be used the defines in the C files need to be PICPART is the number each core handles (this example: 1024). Also the ecore needs to know the length of each row: ROW_LENGTH (this example: 128). Additionally the host needs to know the complete size of the picture: PICSIZE (this example: 16384).

It was tested on a headless parallella destkop board running the (Epiphany toolchain 2016.3.1) 5.2.0

