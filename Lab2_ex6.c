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
	int value = 0;
  
  	char buf[32];
  	while(1){
  		
		
		//Select ADC Channel ch must be 0-7
		ADMUX |= (1 << REFS0) | 0x1;
		
		//Start Single conversion		
		
		ADCSRA=(1<<ADEN)|(1<<ADPS2)|(ADPS1)|(ADPS0);
		
		ADCSRA=(1<<ADSC);

		
		//Wait for conversion to complete
		if(ADCSRA & (1<<ADIF)){
			value = ADC;
			usb_serial_write(ADC,10);
			
		}
		
			
		//Clear ADIF by writing one to it
		ADCSRA|=(1<<ADIF);	
	
  	}
	
}
