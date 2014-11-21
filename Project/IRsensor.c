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

char buffer[25];
uint16_t value;

void setupIR(){
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (ADPS1) | (ADPS0);
	memset(buffer, ' ',25);
}

void selectLeftIR(){

	ADMUX &= ~ADMUX;
	ADMUX |= (1 << REFS0) | (1 << MUX0); //PIN 1
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADIF));
	value = ADC;
	sprintf(buffer, "value = %d \n", value);
	usb_serial_write(buffer, strlen(buffer));
}

void selectMiddleIR(){
	ADMUX &= ~ADMUX;
	ADMUX |= (1 << REFS0); //PIN 0
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADIF));
	value = ADC;
	sprintf(buffer, "value = %d \n", value);
		usb_serial_write(buffer, strlen(buffer));
}

void selectRightIR(){

	ADMUX &= ~ADMUX;
	ADMUX |= (1 << REFS0) | (1 << MUX1); //PIN 2
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADIF));
	value = ADC;
	sprintf(buffer, "value = %d \n", value);
		usb_serial_write(buffer, strlen(buffer));
}

int main(){
	CPU_PRESCALE(CPU_16MHz);
	
	usb_init();
  	setupIR();
  	
  	while(1){
		//selectLeftIR();
		selectRightIR();
		//selectMiddleIR();
		
		
		//_delay_ms(500);
  	}
}
