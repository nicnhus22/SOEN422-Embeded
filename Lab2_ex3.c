#include <avr/io.h>
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00

int main(){
   // Set CPU prescaler
   CPU_PRESCALE(CPU_16MHz);   
   
   // Set PIN7 to be output
   DDRB |= (1<<7);

   TCCR0A = 0b10000011;
   TCCR0B = 0b00000011;
   
   OCR0A = 0;

   // Main loop
   while(1){
      int i=1;
      
      while(i<=255){
         OCR0A = 255 -i;
	 _delay_ms(100);		
         i++;
      }	
   }
}
