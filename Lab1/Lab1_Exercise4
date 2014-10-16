int power[] = {64, 128, 192, 255};

void setup() {
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  for(int i=24; i<=27; i++){
    
    
    analogWrite(i, power[i-24]);  // set the LED on
    Serial.println(power[i-24]);
    delay(100);
    digitalWrite(i, LOW);
    delay(100);
 
       
  }
}
