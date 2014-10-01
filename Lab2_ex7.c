 #define CPU_PRESCALE(n)(CLKPR = 0x80, CLKPR = (n))
 #define F_CPU 16000000 L
 #define CPU_16MHz 0x00

 #include<avr/io.h>
 #include<util/delay.h> 
 #include<stdio.h> 
 #include<avr/interrupt.h> 
 
 #include "usb_serial.h"

/*
   Modify your program so that the previous step is executed in a periodic interrupt handler. 
   In other words use a timer based interrupt.
*/

 int count;

 uint16_t value; // Will hold IR sensor value

 ISR(TIMER0_OVF_vect) {
     count++;
     if (count == 1000) {
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
         sprint(buffer, "value = %d", value);
         usb_serial_write(buffer, strlen(buffer));

         count = 0;
     }
 }


 int main() {

     CPU_PRESCALE(CPU_16MHz);

     usb_init();

     // Fast PWM and toggle OC0A on compare match 
     TCCR0A |= (1 << COM0A0) | (1 << WGM01);

     // Prescaler of clk/1024
     TCCR0B |= (1 << CS00) | (1 << CS02);
     TIMSK0 |= (1 << TOIE0);
     TCNT0 = 0;

     sei();

     // Do something else that isn't timer related
     while (1) {
         int i = 1;
         while (i <= 255) {
             PORTD |= (1 << 6);
             _delay_ms(1000);
             PORTD &= ~(1 << 6);
             _delay_ms(1000);
             i++;
         }
     }
 }
