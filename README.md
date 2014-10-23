SOEN422-Embeded
===============

Compile Code: avr-gcc -mmcu=at90usb1286 -o <output.elf> <input.c> usb_serial.c
Generate Hex: avr-objcopy -O ihex <output.elf> <output.hex>
