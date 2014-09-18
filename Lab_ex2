#include <avr/io.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00

int main(){
 CPU_PRESCALE(CPU_16MHz);   

 // Set DDRD to 0
 DDRD &= ~DDRD;

 // Set PD6 to be output  
 DDRD |= (1<<6);
int value;
while(1){
     value = PIND;
     if(value & (1<<5)){
		PORTD |= (0<<6);
    }
   else {
		PORTD |= (1<<6);
   }
    PORTD &=~(1<<6);
}
	
}
