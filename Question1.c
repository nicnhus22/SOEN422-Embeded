 

 #define CPU_PRESCALE(n)(CLKPR = 0x80, CLKPR = (n))
 #define F_CPU 16000000L
 #define CPU_16MHz 0x00

 #include <avr/io.h>
 #include <stdio.h> 
 #include <avr/interrupt.h>
 #include <string.h> 
 
 #include "usb_serial.h"

 /* The counter in the ISR() will be compared to this value to
  	get the frequency desired. This the interrupt fires ever 1ms,
  	then we compared based of this array:
  		- 100: interrupt every 100ms
  		- 500: interrupt every 500ms
  		- 1000: interrupt every 1s
		- 1500: interrupt every 1.5s
  		- 2000: interrupt every 2s  
  */
 int frequency[6]  = {100, 500, 1000, 1500, 2000 };
 /*
	This will allow us to get 2 different level of brightness.
	We will assign either of these two values to OCR1x to get 
	the desired brightness
  */
 int brightness[4] = {100,150,200,250};

 /* Will hold the user's input command to control frequency/brightness
	Has to be of the form: <LED#> <frequency> <brightness>
							8-bit     8bit        8bit
 */
 uint8_t user_input,
 		 user_led_number = 1,
 		 user_frequency = 0,
 		 user_brightness = 0,
         lengthOfUserInput = 0;

 // Will keep track of the array indexes
 uint8_t led_one_current_frequency = 0,
 		 led_one_current_brightness = 0,
 		 led_two_current_frequency = 0,
 		 led_two_current_brightness = 0;

 // Keep track of the number of Interrupts
 uint16_t timer1_count = 0,
 		  timer2_count = 0;

 
 /*
	This method takes care of updating the frequency and brightness of the first LED
 */
 void updateLedOne(uint8_t frequency, uint8_t brightness){
 	led_one_current_frequency = frequency;
 	led_one_current_brightness = brightness;
 }

 /*
	This method takes care of updating the frequency and brightness of the first LED
 */
 void updateLedTwo(uint8_t frequency, uint8_t brightness){
 	led_two_current_frequency = frequency;
 	led_two_current_brightness = brightness;
 }

 // TIMER1: Interrupt Service Routine called whenever TCNT overflows TOP
 ISR(TIMER1_OVF_vect) {
 	 cli();
     timer1_count++;
     if(timer1_count == frequency[led_one_current_frequency]){
     	// Check whether or not the LED is on
     	if(OCR1A == 0){
     		// Set the brightness to whatever the user entered
        	OCR1A = brightness[led_one_current_brightness];
     	} else {
     		// Turn off LED hooked to OCR1A
        	OCR1A = 0;
     	}

        // Reset counter to trigger timer again
        timer1_count = 0;
     } 
     sei();
 }

 // TIMER0: Interrupt Service Routine called whenever TCNT overflows TOP
 ISR(TIMER0_OVF_vect) {
 	cli();
     timer2_count++;
     if(timer2_count == frequency[led_two_current_frequency]){
     	// Check whether or not the LED is on
     	if(OCR0A == 0){
     		// Set the brightness to whatever the user entered
        	OCR0A = brightness[led_two_current_brightness];
     	} else {
     		// Turn off LED hooked to OCR1A
        	OCR0A = 0;
     	}
     	
        // Reset counter to trigger timer again
        timer2_count = 0;
     } 
     sei();
 }

 /*
	This takes care of clearing all the registers needed
	so we have a fresh start
 */
 void clearRegisters(){
 	TCCR1A = 0;     // Clear TCCR1A
	TCCR1B = 0;     // Clear TCCR1B
	DDRB = 0;		// Clear DDRB
 }

 /*
	This does the setup for Timer1:
		- Phase Correct PWM, TOP at 0x00FF
		- Prescaler clk/64
		- Enable Timer Overflow Interrupt
 */
 void setupTimerOne(){
 	 // 8-bit Phase Correct PWM, TOP at 0x00FF
     TCCR1A |= (1 << WGM10);
     // Set CS11 and CS10 registers to select the prescaler value for 
	 // generating clock for the timer. Here it is clk/64
	 TCCR1B |= (1 << CS11) | (1 << CS10);
	 // Enable Timer Overflow Interrupt for Timer1
	 TIMSK1 |= (1 << TOIE1);
 }

 /*
	This does the setup for Timer0:
		- Phase Correct PWM, TOP at 0x00FF
		- Prescaler clk/64
		- Enable Timer Overflow Interrupt
 */
 void setupTimerZero(){
 	 // 8-bit Phase Correct PWM, TOP at 0x00FF
     TCCR0A |= (1 << WGM00);
     // Set CS11 and CS10 registers to select the prescaler value for 
	 // generating clock for the timer. Here it is clk/64
	 TCCR0B |= (1 << CS01) | (1 << CS00);
	 // Enable Timer Overflow Interrupt for Timer1
	 TIMSK0 |= (1<<TOIE0);
 }


 /*
	Main method
 */
 int main() {
     // CPU prescaler
     CPU_PRESCALE(CPU_16MHz);
     // Enable USB communications
     usb_init();
     clearRegisters();

     // Disable interrupts
     cli();
     // Setup timers 
     setupTimerZero();
     setupTimerOne();
     // Enable interrupts
     sei();

	 // Set OC1A and OC0A to be output. Both are hooked to LEDs
     DDRB |= (1<<5) | (1<<7);

     // Set default PWM duty cycle (100) for both LED
     OCR1A = brightness[led_one_current_brightness]; 
     OCR0A = brightness[led_two_current_brightness];

     // Enable interrupts so that the timer can interrupt main program      
     sei();

     // Main loop
     while (1) {

		// This will get the length in bytes of the user input
        lengthOfUserInput = usb_serial_available();

        // If bytes are waiting in buffer to be addressed
        if(lengthOfUserInput != 0){
            // Disable interrupts if the user entered something
         	cli();
            
            while(usb_serial_available()){
            	user_led_number = usb_serial_getchar(); // Get LED number
            	usb_serial_getchar(); // Skip blank
            	user_frequency = usb_serial_getchar(); // Get frequency
            	usb_serial_getchar(); // Skip blank
            	user_brightness = usb_serial_getchar(); // Get brightness
            }
      		
      		// Update the right LED by checking the input from the user
      		if(user_led_number == '1'){
      			updateLedOne(user_frequency, user_brightness);
      		} else if (user_led_number == '2') {
      			updateLedTwo(user_frequency, user_brightness);
      		}

            // Re-Enable interrupts so the ISR function can be called again
      		sei();
         }
     }
 }
