void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
}

void loop() {
  int estado=digitalRead(8);
  Serial.println(estado);
  delay(500);
}
