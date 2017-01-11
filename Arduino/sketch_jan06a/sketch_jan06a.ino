int ledRojo  =  9; //Declaro pin para cátodo del rojo
int ledVerde = 10; //Declaro pin para cátodo del verde
int ledAzul  = 11; //Declaro pin para cátodo del azul
int sensorPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(ledRojo, OUTPUT);  //Configuro el pin 9 como salida
  pinMode(ledVerde, OUTPUT); //Configuro el pin 10 como salida
  pinMode(ledAzul, OUTPUT);  //Configuro el pin 11 como salida
  pinMode(sensorPin,INPUT);
}

void loop() {
  int sensor = analogRead(A0);
  Serial.println(sensor);
  int estado=digitalRead(sensorPin);
  if(estado!=1){
    Serial.println("FUERA DE RANGO");
    delay(500);
  }
  //Amarillo
  if(sensor>=870 && sensor<=897){
    analogWrite(ledRojo,0);
    analogWrite(ledVerde,0);
    analogWrite(ledAzul,255);
    Serial.println("Amarillo");
    delay(3000);
  }
  //Rojo
  if(sensor>=760 && sensor<=775){
    analogWrite(ledRojo,0);
    analogWrite(ledVerde,255);
    analogWrite(ledAzul,255);
    delay(3000);
  }
  //Verde
  if(sensor>=950 && sensor<=990){
    analogWrite(ledRojo,255);
    analogWrite(ledVerde,0);
    analogWrite(ledAzul,255);
    delay(3000);
  }
  //Azul
  if(sensor>=910 && sensor<=930){
    analogWrite(ledRojo,255);
    analogWrite(ledVerde,255);
    analogWrite(ledAzul,0);
    delay(3000);
  }
  analogWrite(ledRojo,255);
  analogWrite(ledVerde,255);
  analogWrite(ledAzul,255);
  delay(1000);
}
