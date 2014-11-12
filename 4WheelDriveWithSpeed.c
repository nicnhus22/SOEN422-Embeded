#include <Wire.h>

char masterInput;
int staticPwmValue;

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
  
    Serial.begin(9600);
    staticPwmValue = 255;
    pinMode(2, OUTPUT);   // Enable1
    pinMode(13, OUTPUT);   // Enable2
    
    pinMode(14, OUTPUT);  // M1 Forward
    pinMode(15, OUTPUT);  // M1 Reverse
    
    pinMode(26, OUTPUT);  // M2 Forward
    pinMode(25, OUTPUT);  // M2 Reverse
   
}

void leftDrive(int direction, int pwmValue){
  if (direction > 0){ //Drive Forward
    analogWrite(14, pwmValue);
    analogWrite(15, 0);
  }
  else if (direction < 0){ //Drive Backwards
    analogWrite(14, 0);
    analogWrite(15, pwmValue);
  }
  else{ //Stop
    analogWrite(14, 0);
    analogWrite(15, 0);
  }
  
}

void rightDrive(int direction, int pwmValue){
  if (direction > 0){ //Drive Forward
    analogWrite(26, 0);
    analogWrite(25, pwmValue);
  }
  
  else if (direction < 0){ //Drive Backwards
    analogWrite(26, pwmValue);
    analogWrite(25, 0);
  }
  else{ //Stop
    analogWrite(26, 0);
    analogWrite(25, 0);
  }
  
}

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

int i=-1; // -1 is back, 1 is front

void backFront(int pwmValue){
  if(i==-1) forward(pwmValue);
  else reverse(pwmValue);
  (i==-1? i=0:i=-1);
}

void loop(){
  digitalWrite(2, HIGH);  // Set Enable
  digitalWrite(13, HIGH); // Set Enable
  if (Serial.available()) {
    staticPwmValue = Serial.parseInt();
  }
  backFront(staticPwmValue);
  Serial.println(staticPwmValue);
  delay(800);
  

  
  
  // Slave address of Teensy
  int SLAVE_ADDRESS = 0x7;
  // Start the USB communication
  Serial.begin(9600);
  // Begin I2C communication with beaglebone
  Wire.begin(SLAVE_ADDRESS);
  // When the BB sends something, execute callback function
  Wire.onReceive(myCallbackFunction);
}

