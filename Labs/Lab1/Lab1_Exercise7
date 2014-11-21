#include <TimerThree.h>

int power[] = {64, 128, 192, 255};

void printWithTimer(void){
  Serial.println("hello");
  Serial.println(analogRead(45));
}

void setup(void) {
  // Hooked to the timer
  pinMode(45, INPUT);
  
  // Gotta use TimerThree
  Timer3.initialize(1000000);
  Timer3.attachInterrupt(printWithTimer);
  
  Serial.begin(9600);
}

void loop() {
  
}



