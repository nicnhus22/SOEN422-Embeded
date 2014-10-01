#include <avr/io.h>
#include <util/delay.h>
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00

/*
   Modify your program to receive commands over the serial monitor such that the 
   frequency of the blinking LED or frequency of the interrupt can be adjusted.
*/
int main(){
   
    // Set CPU prescaler
    CPU_PRESCALE(CPU_16MHz);

    uint8_t lengthOfUserInput;
    uint8_t userInput;

    // Set PIN7 to be output
    DDRB |= (1<<7);

    // Main loop
    while(1){
        // This will get the length in bytes of the user input
        lengthOfUserInput = usb_serial_available();
        
        // If bytes are waiting in buffer to be addressed
        if(lengthOfUserInput != 0){
            
            // This will read one byte 0-255 off the buffer
            // Still need to figure how to read the whole data.
            // Edit: This will read everyting and echo it.
            while(1){
         		userInput = usb_serial_getchar();
         		if (userInput >= 0) usb_serial_putchar(n);
            }
        }
    }
}
