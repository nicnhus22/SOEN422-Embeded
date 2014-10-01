#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "usb_serial.h"

/*
   Install an IR sensor on an A/D input. Modify your program to read the analog value from the IR Sensor
   and print the value to the serial monitor at a rate of approximately once per second.
*/
int main(){
	CPU_PRESCALE(CPU_16MHz);
	
	usb_init();
	
	uint16_t value;
  
  	//Select ADC Channel ch must be 0-7
	ADMUX |= (1 << REFS0) | 0x1;
	
	ADCSRA=(1<<ADEN) | (1<<ADPS2) | (ADPS1) | (ADPS0);
  	
  	char buffer[25];
  	memset(buffer, ' ',25);
  	
  	while(1){
	
		//Start Single conversion		
		ADCSRA=(1<<ADSC);

		//Wait for conversion to complete
		while(ADCSRA & (1<<ADIF));
		
		// Read value from ADC
		value = ADC;
			
		sprint(buffer, "value = %d", value);
		usb_serial_write(buffer, strlen(buffer));
		
		_delay_ms(1000);
  	}
	
}
