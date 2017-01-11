/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#define MAXANGLE 160

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int button1Pin = 4;
const int button2Pin = 5;

int pos = 0;

int buttonState1 = 0;    // variable to store the button1 state}
int buttonState2 = 0;    // variable to store the button2 state

void setup() {
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  // initialize the buttons pin as an input:
  pinMode(button1Pin , INPUT);
  pinMode(button2Pin , INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState1 = digitalRead(button1Pin);
  buttonState2 = digitalRead(button2Pin);
  if (buttonState1 == HIGH){
    pos++;      
  }
  Serial.println(buttonState1+buttonState2);
  /*if (buttonState2 == HIGH){
    pos--;      
  } 
  if (pos < 0){
    pos = 0;  
  }else if (pos > MAXANGLE){
    pos = MAXANGLE;
  }
  
  myservo.write(pos); */   
  delay(15);
  }

