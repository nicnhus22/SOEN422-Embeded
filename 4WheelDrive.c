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
    digitalWrite(led, LOW); // Turn the LED off
  }
  else{
    digitalWrite(led, HIGH); // Turn the LED on
  }
}

void setup(){
  
   
    pinMode(2, OUTPUT);   // Enable1
  
    pinMode(27, OUTPUT);  // M1 Forward
    pinMode(16 , OUTPUT);  // M1 Reverse
    
    pinMode(14, OUTPUT);  // M1 Forward
    pinMode(15, OUTPUT);  // M1 Reverse
    
    pinMode(26, OUTPUT);  // M2 Forward
    pinMode(25, OUTPUT);  // M2 Reverse
    
    pinMode(13, OUTPUT);   // Enable2
  
    
    
    //pinMode(16, OUTPUT); //M2 FORWARD *
    //pinMode(24, OUTPUT);  //M2 reverse *
   
}

void leftDrive(int direction){
  if (direction > 0){ //Drive Forward
    analogWrite(14, 255);
    analogWrite(15, 0);
  }
  else if (direction < 0){ //Drive Backwards
    analogWrite(14, 0);
    analogWrite(15, 255);
  }
  else{ //Stop
    analogWrite(14, 0);
    analogWrite(15, 0);
  }
  
}

void rightDrive(int direction){
  if (direction > 0){ //Drive Forward
    analogWrite(26, 0);
    analogWrite(25, 255);
  }
  
  else if (direction < 0){ //Drive Backwards
    analogWrite(26, 255);
    analogWrite(25, 0);
  }
  else{ //Stop
    analogWrite(26, 0);
    analogWrite(25, 0);
  }
  
}


void loop(){
  digitalWrite(2, HIGH); // Set Enable
  
  digitalWrite(13, HIGH); // Set Enable
  
  leftDrive(-1);
  rightDrive(1);
  
  
  //analogWrite(16, 0);
  //analogWrite(24, 255);
  
  // Slave address of Teensy
  int SLAVE_ADDRESS = 0x7;
  // Start the USB communication
  Serial.begin(9600);
  // Begin I2C communication with beaglebone
  Wire.begin(SLAVE_ADDRESS);
  // When the BB sends something, execute callback function
  Wire.onReceive(myCallbackFunction);
}
