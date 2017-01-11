int LDRPins[]={2,3,4,5};
int notas[]={1270,1394,1530,1749,1892,1940,1534};
int speakerPin = 11;
String patron1,patron2;
int LDRValue;

void setup() {
   Serial.begin(9600); 
}

void loop() {
  for(int i=31;i<65535;i=i+100){
      tone(11,i);
      delay(200);
      Serial.println(i);
  }
}
