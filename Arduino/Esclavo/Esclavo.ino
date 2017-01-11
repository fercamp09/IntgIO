#include <Wire.h>

/*
 * Arreglo de pines para controlar LDRs
 */
int LDRPins[]={2,3,4,5,6,7,8,9,10};
int LDRValue = 0; 

void setup() {
  Wire.begin(8);                
  Wire.onRequest(requestEvent); 
}

void loop() {
}

void requestEvent() {
  char LDRs[10]="111111111";
  for(int i=0;i<9;i++){
      LDRValue = digitalRead(LDRPins[i]);
      if(LDRValue==0)
        LDRs[i]='0';
      else
        LDRs[i]='1';
  }
  Wire.write(LDRs);
}

