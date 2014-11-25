#include <TimerOne.h>

int power[] = {64, 128, 192, 255};

void setup() {
  // 
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  
  // Hooked to the timer
  pinMode(27, OUTPUT);
  
  Serial.begin(9600);
  
  // Init timer to 2sec
  Timer1.initialize(2000000);
  Timer1.pwm(27, 512);
}

void loop() {
  
  for(int i=24; i<=26; i++){
    digitalWrite(i, power[i-24]);  // set the LED on
    delay(100);
    analogWrite(i, LOW);
    delay(100);
  }
  
}

