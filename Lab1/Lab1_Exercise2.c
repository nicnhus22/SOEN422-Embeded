void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);

}

void loop() {
  
  Serial.println(digitalRead(7));
  if(!digitalRead(7)){
    digitalWrite(6, HIGH);
  } 
  else{
    digitalWrite(6, LOW);
  }
}
