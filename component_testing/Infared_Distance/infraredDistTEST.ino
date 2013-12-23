int x;

void setup() {
  Serial.begin(9600); //initialize baud rate to 9600
}

void loop() {
  x = analogRead(2); //read value from analog pin 2 (A2)
  Serial.println(x); //print value
  
}
