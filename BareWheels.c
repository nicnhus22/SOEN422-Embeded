#include <avr/io.h>
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00

unit8_t SLOW = 150;
unit8_t FAST = 255;

/*
   Write a sketch that cycles through 4 levels of brightness on an LED array.
   Note: We made it fade in-out instead of four level of brightness
*/
void setup(){

    TCCR0A &= ~TCCR0A;
    TCCR0B &= ~TCCR0B;
    
    DDRD |= (1<<2); //Enable1 on pin 2 (PD2)
    DDRC |= (1<<3); //Enable2 on pin 13 (PC3) 
    
    setupTimer0();
    setupTimer2();
    setupEnables();
}

// Setup enables
void setupEnables(){
    PIND |= (1<<2);
    PINC |= (1<<3);
}

// This timer will control the left wheels
// ChannelA: Forward
// ChannelB: Reverse
void setupTimer0(){

    DDRB |= (1<<7); //m1 forward OCR0A
    DDRD |= (1<<0); //m1 reverse OCR0B

    TCCR0A |= (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00) | (1<<WGM01); 
    TCCR0B |= (1<<CS00);  //phase correct with OCRA output compare

}

// This timer will control the right wheels
// ChannelA: Forward
// ChannelB: Reverse
void setupTimer2(){

    DDRB |= (1<<4); //m2 forward
    DDRD |= (1<<1); //m2 reverse

    TCCR2A |= (1<<COM2A1) | (1<<COM2B1) | (1<<WGM20) | (1<<WGM21); 
    TCCR2B |= (1<<CS20);  //phase correct with OCRA output compare  

}


void leftDrive(uint8_t direction, uint8_t pwmValue){
  if (direction > 0){ //Drive Forward
    OCR0A = pwmValue;
    OCR0B = 0;
  }
  else if (direction < 0){ //Drive Backwards
    OCR0A = 0;
    OCR0B = pwmValue;
  }
  else{ //Stop
    OCR0A = 0;
    OCR0B = 0;
  }
  
}

void rightDrive(uint8_t direction, uint8_t pwmValue){
  if (direction > 0){ //Drive Forward
    OCR2A = pwmValue;
    OCR2B &= ~OCR2B;
  }
  else if (direction < 0){ //Drive Backwards
    OCR2A = 0;
    OCR2B = pwmValue;
  }
  else{ //Stop
    OCR2A = 0;
    OCR2B = 0;
  }
}




int main(){
   // Set CPU prescaler
   CPU_PRESCALE(CPU_16MHz);   
   
   setup(); //sets phase correct on timer 0 for the wheels.
   
   leftDrive(1,255);
   //rightDrive(1,255);
   
}
