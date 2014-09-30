   
   
   #include <avr/io.h>
   #include <util/delay.h>
   #include <stdio.h>
   
   #include "usb_serial.h"
   
   #define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
   #define F_CPU 16000000L
   #define CPU_16MHz 0x00
      
   
   int main(){
   	CPU_PRESCALE(CPU_16MHz);
   	
   	usb_init();
  
  	while(1){
  		usb_serial_putchar('a');
		
		//Select ADC Channel ch must be 0-7
		ADMUX |= (1 << REFS0) | 0x2;
		
		//Start Single conversion
		ADCSRA|=(1<<ADSC);
		
		//Wait for conversion to complete
		while(!(ADCSRA & (1<<ADIF)));
		
		//Clear ADIF by writing one to it
		ADCSRA|=(1<<ADIF);
		
		_delay_ms(1000);
	
  	}
   }
                               
