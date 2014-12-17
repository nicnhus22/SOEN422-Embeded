

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define F_CPU 16000000L
#define CPU_16MHz 0x00


void setup(){
    // Set CPU prescaler
    CPU_PRESCALE(CPU_16MHz); 
    
    setupWheels();
}

void loop(){
    testWheels();
    rotateServo();
}
