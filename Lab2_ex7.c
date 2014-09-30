 #include <avr/io.h>
 #include <util/delay.h>
 #include <stdio.h>
   #include <avr/interrupt.h>
   #include "usb_serial.h"
   
   #define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
   #define F_CPU 16000000L
   #define CPU_16MHz 0x00
   
   int count; 
   ISR(TIMER0_OVF_vect)
   {
   	count++;
  	if(count==1000)
  	{
  		//Select ADC Channel ch must be 0-7
		//ADMUX |= (1 << REFS0) | 0x2;
	
		//Start Single conversion
		//ADCSRA|=(1<<ADSC);
	
		//Wait for conversion to complete
		//while(!(ADCSRA & (1<<ADIF)));
	
		//Clear ADIF by writing one to it
		//ADCSRA|=(1<<ADIF);
  		
	  	//count = 0;
	  	 }	
	}
	 
	
        int main(){ 


	usb_init();
	 usb_serial_putchar('a');	
	//fast PWM and toggle OC0A on compare match 
	TCCR0A |= (1<<COM0A0) | (1<<WGM01);

	//prescaler of clk/1024
	TCCR0B |= (1<<CS00) | (1<<CS02); 

	// Period is roughly 1.2 seconds.
	//OCR1A = 20000;

	TIMSK0 |= (1 << TOIE0);
	  TCNT0=0;
          CPU_PRESCALE(CPU_16MHz);
	  sei();
	  
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
