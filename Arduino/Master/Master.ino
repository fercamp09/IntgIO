#include <Wire.h>

#define TIME_OUT  5
int notas[]={3830,3400,3038,2864,2550,2272,2028,1912};
//int notas[]={931,231,331,831,531,631};
int speakerPin = 11,val,val2,time;
String LDRs;

void setup() {
  Wire.begin();       
  Serial.begin(9600); 
  pinMode(A3, INPUT);
}

void loop() {
  Serial.println(analogRead(A3));
  //musica();
  delay(200);
}

String leerLDRs(){
    String LDRs;
    Wire.requestFrom(8, 9);   
    while (Wire.available()) { 
      char c=Wire.read();
      LDRs +=c;   
    }
    delay(500);
    return LDRs; 
}

int activadoLDRs(String LDRs,int tapados[]){
  int k=0;
  for(int i =0; i<9 ; i++){
      if(LDRs.substring(i,i+1)=="0"){
          tapados[k]=i;
          k+=1;
      }
  }
  return k;
}

int unicoLDR(String LDRs){
  int k=0;
  for(int i =0; i<9 ; i++){
      if(LDRs.substring(i,i+1)=="0"){
          Serial.println(i);
          return i;
      }
  }
  return -1;
}


void musica(){
  int patron1[]={},patron2[]={},k=0;
  do{
    LDRs=leerLDRs();
    val=unicoLDR(LDRs);
    Serial.println(val);
  }while(val==-1);
  time=0;
  val2=-1;
  while(time<TIME_OUT){
    if(val!=-1){
      time=0;
      if(val2!=val){
        patron1[k]=val;
        k+=1;
      }
      tone(speakerPin,notas[val]);
      val2=val;
    }
    else{
      time=time+1;
      delay(250);
      noTone(speakerPin);
    }
    LDRs=leerLDRs();
    val=unicoLDR(LDRs);
  }
  for(int i=0;i<k;i++){
    Serial.println(patron1[i]);
  }
  delay(5000);
}
