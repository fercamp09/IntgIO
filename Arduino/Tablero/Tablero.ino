int redPin = 9;     //pwm analog out for all red LEDs
int bluePin = 11;    //pwm analog out for all blue LEDs
int greenPin = 10;  //pwm analog out for all green LEDs
int ledCount = 9;   //# of RGB commone cathode LEDs

int vibratorPin = 5; // LED connected to digital pin 13
int inMagnetic = 6;   // pushbutton connected to digital pin 7
int val = 0;     // variable to store the read value
int groundPin[] = {0,1,2,3,4,7,8,12,13}; //digital grounds

struct RGB {
  byte r;
  byte g;
  byte b;
};

RGB ledArray[] = {{0,255,0},{0,255,0},{0,0,255},{0,255,0},{0,255,0},{0,0,255},{0,255,0},{0,255,0},{0,0,255}};

    
void setup()  
{   
  Serial.begin(9600);
  pinMode(vibratorPin, OUTPUT);      // sets the digital pin 13 as output
  pinMode(inMagnetic, INPUT);      // sets the digital pin 7 as input
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //declare grounds and debug all LEDs
  for(int i=0; i<ledCount; i++)
  {

    pinMode(groundPin[i],OUTPUT); //cycle each ground pin mode
    digitalWrite(groundPin[i],LOW);
  }

  
}   
    
void loop()
{   

  val = digitalRead(inMagnetic);   // read the input pin
     // sets the LED to the button's value
  //multiplex the ledArray values through each LED
  Serial.println(val);
  if(!val){
      analogWrite(vibratorPin,200); 
      analogWrite(redPin, (255,0,0)); //red pin pwm set for specific LED color
      analogWrite(greenPin, (0,255,0));
      analogWrite(bluePin, (0,0,255));
      for(int i=0; i<ledCount; i++)
        digitalWrite(groundPin[i],HIGH);
      delay(1000);
  }
  else{
    for(int i=0; i<ledCount; i++)
      digitalWrite(groundPin[i],LOW);
  }
  delay(500);
}
