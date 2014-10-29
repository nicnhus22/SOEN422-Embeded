#include <Wire.h>
char myChar;

void myCallbackFunction(int nbOfBytes){
  
  for(int i=0; i < nbOfBytes; i++){
    myChar = Wire.read();
    Serial.write(myChar);
  }
  
  
}

void setup(){
   
}


void loop(){
 
  int SLAVE_ADDRESS = 0x7;
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  
  Wire.onReceive(myCallbackFunction);
}
