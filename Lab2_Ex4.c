   
   
   #include <avr/io.h>
   #include <util/delay.h>
   #include <stdio.h>
   
   #include "usb_serial.h"
   
   
   #define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
   #define F_CPU 16000000L
   #define CPU_16MHz 0x00
   
   int main(){
          usb_init();
          
          CPU_PRESCALE(CPU_16MHz);
          DDRB |= (1<<7);
          TCCR0A = 0b10000011;
          TCCR0B = 0b00000011;
          OCR0A = 0;
  
          char buf[32];
 
  while(1){
          int i=1;
          while(i<=255){
                  OCR0A = 255 -i;
                 sprintf(buf,"%d",255-i); 
                 usb_serial_putchar((uint8_t)buf);
                  _delay_ms(100);
                 i++;
          }
  }
}
                               
