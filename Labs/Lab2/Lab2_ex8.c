 #define CPU_PRESCALE(n)(CLKPR = 0x80, CLKPR = (n))
 #define F_CPU 16000000L
 #define CPU_16MHz 0x00

 #include <avr/io.h>
 #include <util/delay.h> 
 #include <stdio.h> 
 #include <avr/interrupt.h>
 #include <string.h> 
 
 #include "usb_serial.h"


/*
   Get input from user
*/


 uint16_t count;

 uint16_t value; // Will hold IR sensor value
 
 uint8_t lengthOfUserInput;
 uint16_t userInput, TIMER_COUNT = 100;

 ISR(TIMER0_OVF_vect) {
     cli();
     count++;
     if(count == TIMER_COUNT){
        
        //Select ADC Channel ch must be 0-7
	ADMUX |= (1 << REFS0) | 0x1;
	
	// Start single conversion
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (ADPS1) | (ADPS0);
	ADCSRA |= (1 << ADSC);
	
	char buffer[25];
	memset(buffer, ' ', 25);
	
	//Wait for conversion to complete
	while (ADCSRA & (1 << ADIF));
	
	// Read value from ADC
	value = ADC;
	
	// Print the value to user
	sprintf(buffer, "value = %d\nAnd timer count is: %d\n", value, TIMER_COUNT);
	usb_serial_write(buffer, strlen(buffer));
        
        count = 0;
     } 
     sei();
 }


 int main() {

     CPU_PRESCALE(CPU_16MHz);

     usb_init();

     // Fast PWM and toggle OC0A on compare match 
     TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);

     // Prescaler of clk/1024
     TCCR0B |= (1 << CS00) | (1 << CS02);
     TIMSK0 |= (1 << TOIE0);
     
     sei();

     // Main loop
    while(1){
    
        // This will get the length in bytes of the user input
        lengthOfUserInput = usb_serial_available();
        
        // If bytes are waiting in buffer to be addressed
        if(lengthOfUserInput != 0){
         	cli();
      		userInput = usb_serial_getchar();
      		switch(userInput){
      		   case '+':
      		      // The limit is 50
      		      if(TIMER_COUNT!=50)
      		         TIMER_COUNT -= 50;
      		      break;
      		   case '-':
      		      // The limit is 1000
      		      if(TIMER_COUNT!=1000)
      		         TIMER_COUNT += 50;
      		      break;
      		   default:
      		      break;
      		} 
      		sei();
         }
     }
 }
