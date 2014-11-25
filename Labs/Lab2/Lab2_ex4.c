
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
   
#include "usb_serial.h"
   
   
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00
   
/*
   Modify your sketch to print the brightness mode to the teensy monitor.
*/
int main(){
   // Set CPU prescaler
   CPU_PRESCALE(CPU_16MHz);
   
   usb_init();
          
   DDRB |= (1<<7);
   TCCR0A = 0b10000011;
   TCCR0B = 0b00000011;
   OCR0A = 0;
  
   // 32but buffer to hold value
   char buf[32];
   memset(buffer, ' ', 32);

   while(1){
      int i=1;
      
      while(i<=255){
         OCR0A = 255 -i;
                 
         // Print the value to user
         sprint(buffer, "value = %d", 255-i);
         usb_serial_write(buffer, strlen(buffer));
                 
         _delay_ms(100);
                 
         i++;
      }
   }
}
                               
