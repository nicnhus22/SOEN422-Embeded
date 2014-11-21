#include <avr/io.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00

/*
   Write a sketch that turns on an LED array element when a pin of your choice is grounded 
   but the LED element must turn off when the same pin is physically set to HIGH
*/
int main(){
	
   // Set CPU prescaler
   CPU_PRESCALE(CPU_16MHz);   

   // Set DDRD to 0
   DDRD &= ~DDRD;

   // Set PD6 to be output pin  
   DDRD |= (1<<6);

   // This will change whethere we GROUND the pin or not
   uint16_t value;

   while(1){
      // Read PIN value into variable
      value = PIND;
      
      // Turn on LED if PIN is grounded
      if(value & (1<<5)){
         PORTD |= (0<<6);
      } else {
	 PORTD |= (1<<6);
      }
      
      // Turn off LED
      PORTD &=~(1<<6);
   }
}
