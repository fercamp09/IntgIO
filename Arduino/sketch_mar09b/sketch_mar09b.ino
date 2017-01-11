
const int led = 11;
void setup() {
  pinMode(led,OUTPUT);

}

void loop() {
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(led, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}
