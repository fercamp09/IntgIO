const int groundpin = A0;             // analog input pin 4 -- ground
const int powerpin = A4;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis

void setup() {
  Serial.begin(9600);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

void loop() {
  int x = analogRead(xpin);
  String cad= (String) x;
  Serial.println(cad);
  Serial.flush();
  delay(100);
}

