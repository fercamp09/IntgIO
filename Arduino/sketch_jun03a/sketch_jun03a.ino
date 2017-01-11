#define SIZE 70//Size of moving average
#define SENSIVITY 0.04

// CONSTANTES CONFIGURACION ACELEROMETRO
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 14;              // analog input pin 5 -- voltage
const int xpin = A1;                  // x-axis
const int ypin = A2;                  // y-axis
const int zpin = A3;                  // z-axis
double MAX_G = 3;
double V_ARDUINO_REF = 5;
double V_ACC_REF = 3.3;
double ADC_BITS = 1024;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  // obtiene valores del acc
    int x=0,y=0,z=0,i;
    for(i=0;i<SIZE;i++){
      x =x + analogRead(xpin);
      y =y + analogRead(ypin);
      z =z + analogRead(zpin);
    }
    x = x/SIZE;
    y = y/SIZE;
    z = z/SIZE;
    x = analogRead(xpin);
    y = analogRead(ypin);
    z = analogRead(zpin);
    double xG = (V_ARDUINO_REF*(x/ADC_BITS)*(2*MAX_G/V_ACC_REF) - MAX_G) + SENSIVITY;
    double yG = (V_ARDUINO_REF*(y/ADC_BITS)*(2*MAX_G/V_ACC_REF) - MAX_G) + SENSIVITY;
    double zG = (V_ARDUINO_REF*(z/ADC_BITS)*(2*MAX_G/V_ACC_REF) - MAX_G) + SENSIVITY;
    // imprime el valor del eje X
    Serial.print(String(x));
    Serial.print("\t");
    // imprime el valor del eje Y
    Serial.print(String(y));
    Serial.print("\t");
    // imprime el valor del eje Z
    Serial.print(String(z));
    Serial.println();
    delay(10);
}


