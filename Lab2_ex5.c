   
   
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
          DDRB &= ~DDRB;
          
          // Set port 6 to Output
          DDRD |= (1<<6);
          
          // Set led to output
	  DDRB |= (1 << 5);
	  
	  // 0A handling the voltage variation, OB pulsing. 16BIT-Timer.
	  TCCR1A |= (1<<COM1A0);
	  TCCR1B |= (1 << WGM12) | (1<<CS12) | (1<<CS10); 
	  
	  // Set mode to CTC, compares with OCR1A, cs= fcpu/1024 = roughly 2 clocks per 1ms.
	  // Period is roughly 2 seconds.
	  OCR1A = 2 * 2500;
  
 
  while(1){
          int i=1;
          while(i<=255){
          	 PORTD |= (1<<6);
                 _delay_ms(1000);
                 PORTD &= ~(1<<6);
                 _delay_ms(1000);
                 i++;
          }
  }
}
                               
