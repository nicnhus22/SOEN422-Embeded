SOEN422-Embeded
===============

Command compile code:

avr-gcc -mmcu=at90usb1286 -O -o ex4out.o ex4.c usb_serial.c

Make it an hex file:

avr-objcopy -O ihex ex4out.o output.hex

Load it!

Link to get the internet on the BeagleBone

http://stackoverflow.com/questions/19481415/share-the-internet-access-from-laptop-to-beaglebone-black-and-then-access-it-thr
