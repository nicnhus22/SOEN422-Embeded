#include <Wire.h>

char masterInput;

// Will hook LED number 13
int led = 13;

void myCallbackFunction(int nbOfBytes){
  	// Read the input from the BeagleBone Master
	for(int i=0; i < nbOfBytes; i++){
		masterInput = Wire.read();
	}

	// If the user inputs 0 then turn off LED
	if(masterInput == '0'){
		digitalWrite(led, LOW);   // Turn the LED off
	}else{
		digitalWrite(led, HIGH);   // Turn the LED on
	}

}

void setup(){
	// Initialize the digital pin as an output.
	pinMode(led, OUTPUT);
}

void loop(){
  	// Slave address of Teensy
	int SLAVE_ADDRESS = 0x7;
	// Start the USB communication
	Serial.begin(9600);
	// Begin I2C communication with beaglebone
	Wire.begin(SLAVE_ADDRESS);
	// When the BB sends something, execute callback function
	Wire.onReceive(myCallbackFunction);
}
