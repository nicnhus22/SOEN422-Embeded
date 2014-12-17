
/*-------------------------------------------------------------------
 *	This part of the code provides low level functions  to
 *	control the wheels. It sets the timers to generate PWM
 *	values and provides two functions:
 *		- leftDrive(int direction, int pwm);
 *		- rightDrive(int direction, int pwm);
 *
 *-------------------------------------------------------------------
 */

// This timer will control the left wheels
void setupTimer3(){

    DDRC |= (1<<1); // ENABLE1

    TCCR3A |= (1<<COM3A1) | (1<<COM3B1) | (1<<WGM30) | (1<<WGM31); 
    TCCR3B |= (1<<CS30); 

}

// This timer will control the right wheels
void setupTimer0(){

    DDRC |= (1<<0); // ENABLE1

    TCCR0A |= (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00) | (1<<WGM01); 
    TCCR0B |= (1<<CS00); 

}

void setupWheels(){ 
    setupTimer3();
    setupTimer0();
}

void clearLeftMotorRegisters(){
    PORTC &= ~(1<<6);
    PORTC &= ~(1<<5);
    
    DDRC &= ~(1<<6);
    DDRC &= ~(1<<5);
}


void leftDrive(int direction, int pwmValue){
    clearLeftMotorRegisters();

    if(direction < 0){ // Forward
    	PORTC |= (1<<1);
    
    	DDRC |= (0<<6); // OCR3A
    	DDRC |= (1<<5); // OCR3B
    
    	OCR3A = 0;
    	OCR3B = pwmValue;
    }else if(direction > 0) { // Reverse
    	PORTC |= (1<<1);
    
    	DDRC |= (1<<6); // OCR3A
    	DDRC |= (0<<5); // OCR3B
    
    	OCR3A = pwmValue;
    	OCR3B = 0;
    }else { // Stop
    	PORTC |= (0<<1);
    }
}

void clearRightMotorRegisters(){
    PORTB &= ~(1<<7);
    PORTD &= ~(1<<0);
    
    DDRB &= ~(1<<7);
    DDRD &= ~(1<<0);
}

void rightDrive(int direction, int pwmValue){
    clearRightMotorRegisters();

    if(direction > 0){ // Forward
    	PORTC |= (1<<0);
    
    	DDRB |= (1<<7); // OCR3A
    	DDRD |= (1<<0); // OCR3B
    
    	OCR0A = 0;
    	OCR0B = pwmValue;
    }else if(direction < 0) { // Reverse
    	PORTC |= (1<<0);
    
    	DDRB |= (1<<7); // OCR3A
    	DDRD |= (1<<0); // OCR3B
    
    	OCR0A = pwmValue;
    	OCR0B = 0;
    }else { // Stop
    	PORTC |= (0<<0);
    }
}


/*-------------------------------------------------------------------
 *	This part of the code provides higher level functions to
 *	control the wheels. Functions are the following:
 *		- forward(int pwmValue);
 *		- reverse(int pwmValue);
 *		- turnLeft(int pwmValue);
 *		- turnRight(int pwmValue);
 *		- rotateLeft(int pwmValue);
 *		- rotateRight(int pwmValue);
 *
 *-------------------------------------------------------------------
 */
 
void forward(int pwmValue){
  leftDrive(1, pwmValue);
  rightDrive(1, pwmValue);
}

void reverse(int pwmValue){
  leftDrive(-1, pwmValue);
  rightDrive(-1, pwmValue);
}

void turnLeft(int pwmValue){
  leftDrive(0, pwmValue);
  rightDrive(1, pwmValue);
}

void turnRight(int pwmValue){
  leftDrive(1, pwmValue);
  rightDrive(0, pwmValue);
}

void rotateLeft(int pwmValue){
  leftDrive(-1, pwmValue);
  rightDrive(1, pwmValue);
}

void rotateRight(int pwmValue){
  leftDrive(1, pwmValue);
  rightDrive(-1, pwmValue);
}

void testWheels(){
   forward(255);
}




