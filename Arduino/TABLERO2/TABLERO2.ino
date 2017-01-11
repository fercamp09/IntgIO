/*
   rojo - luces
   negro - vibración
   azul - sonido
*/
#define TOTALRGB 9
#define PINVIBRADOR 5
#define PINMAGNETICO 6
#define PINRECOMPENSA A0
//#define PINMELODIA A

/*
 * PWM para colores
 */

int pinRojo = 11;
int pinVerde = 10;
int pinAzul = 9;

/*
 * Arreglo de pines para controlar RGBs
 */
int groundPin[TOTALRGB] = {3, 1, 2, 0, 4, 7, 8, 12, 13};

/*
 * Configuración de estímulos
  */
  int luces = 0 ;
  int vibracion = 0;
  int sonido = 0;

  int magnetico = 0;

  /*
   * Variables temporales
   */
  int jtemp = 0;
  int tempRed = 0;
  int tempGreen = 0;
  int tempBlue = 0;
  int contImitacion;
  int randomRGB = 0;

void setColor(int green, int blue, int red)
{
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(pinRojo, red);
  analogWrite(pinVerde, green);
  analogWrite(pinAzul, blue);
}

void setupRGB()
{
  for (int i = 0; i < TOTALRGB; i++)
  {
    pinMode(groundPin[i], OUTPUT);
  }
}

void encenderRGB(int pin, int rojo, int verde, int azul)
{
  for(int i = 0; i<TOTALRGB; i++)
  {
    if(i == pin)
    {
      digitalWrite(groundPin[i], 1);
      setColor(rojo, verde, azul);
    }
    else
    {
      digitalWrite(groundPin[i], 0);
    }
  }
}

void encenderTablero(int rojo,int verde,int azul)
{
  for(int i = 0; i<TOTALRGB; i++)
  {
    digitalWrite(groundPin[i], 1);
    setColor(rojo, verde, azul);
  }
}

void apagarTablero()
{
  for(int i = 0; i<TOTALRGB; i++)
  {
    digitalWrite(groundPin[i], 0);
    setColor(0, 0, 0);
  }
}

void apagarRGB(int pin)
{
  for(int i = 0; i < TOTALRGB; i++)
  {
    if(groundPin[i] = pin)
    digitalWrite(groundPin[i], 0);
  }
}

void recompensar()
{
  digitalWrite(PINVIBRADOR, vibracion);

  for(int i =0; i < 5; i++)
  {
    encenderTablero(255, 255, 0);
    delay(300);
    encenderTablero(80, 0, 80);
    delay(300);
    encenderTablero(0, 255, 255);
    delay(300);
    encenderTablero(255, 0, 0);
    delay(300);
    encenderTablero(0, 255, 0);
    delay(300);
    encenderTablero(0, 0, 255);
    delay(300);
  }
}

void colores() 
{
  int temp[3] = {-1, -1, -1};
  jtemp = 0;
  while (!temp[2]==(-1)) { // llena un arreglo temporal "temp" con RGBs no repetidos.
    randomRGB = random(0, 10);
    Serial.println("random " + String(randomRGB));
    if (!(groundPin[randomRGB]==(temp[0])) && (!(groundPin[randomRGB]==(temp[1]))) && (!(groundPin[randomRGB]==(temp[2])))) {
      temp[jtemp] = groundPin[randomRGB];
      jtemp++;
    }
  }
  tempRed = random(0,100);
  tempGreen = random(100,255);
  tempBlue = random(100,255);

    while (contImitacion < 5) {
    int value_recompensa =  analogRead(PINRECOMPENSA);
    encenderRGB(temp[2], 255, 0, 0);
    delay(400);
    encenderRGB(temp[1], tempRed, tempGreen, tempBlue);
    encenderRGB(temp[0], tempRed, tempGreen, tempBlue);
    
    if (value_recompensa > 927 && value_recompensa < 945) {
      contImitacion++;
    }
  }
}

void imitacion()
{
  delay(1000);
  tempRed = random(100,255);
  tempGreen = random(100,255);
  tempBlue = random(100,255);
  while (1) {
    int value_recompensa =  analogRead(PINRECOMPENSA);
    magnetico = digitalRead(PINMAGNETICO);   // read the input pin
    digitalWrite(PINVIBRADOR, !magnetico);    // sets the LED to the button's value
    if(magnetico)
    {
      encenderTablero(tempRed, tempGreen, tempBlue);
    }
    else
    {
      apagarTablero();
    }

    if (value_recompensa > 927 && value_recompensa < 945) {
      Serial.println(" ---- Recompensa");
      recompensar();
    }
    Serial.println(" ---- jugando");
  }
}

void configurar() {
  int value_recompensa =  analogRead(PINRECOMPENSA);
  Serial.println(value_recompensa);
  if (value_recompensa < 94 && value_recompensa > 80) {
    //Serial.println("botón rojo");
    luces = 1;
    vibracion = 0;
    sonido = 0;
  }
  else if (value_recompensa < 514 && value_recompensa > 510) {
    //Serial.println("botón negro");
    luces = 0;
    vibracion = 1;
    sonido = 0;
  }
  else if (value_recompensa > 170 && value_recompensa < 176) {
    //Serial.println("botón azul");
    luces = 0;
    vibracion = 0;
    sonido = 1;
  }
  else if (value_recompensa > 237 && value_recompensa < 241) {
    //Serial.println("rojo y azul");
    luces = 1;
    vibracion = 0;
    sonido = 1;

  }
  else if (value_recompensa > 535 && value_recompensa < 539) {
    //Serial.println("rojo y negro");
    luces = 1;
    vibracion = 1;
    sonido = 0;
  }
  else if (value_recompensa > 579 && value_recompensa < 582) {
    //Serial.println("todas");
    luces = 1;
    vibracion = 1;
    sonido = 1;
  }
  else if (value_recompensa > 557 && value_recompensa < 563) {
    //Serial.println("azul negro");
    luces = 0;
    vibracion = 1;
    sonido = 1;
  }
  else if (value_recompensa > 927 && value_recompensa < 945) {
    //while(value_recompensa<929 || value_recompensa>945);
    Serial.println(" ---- A jugar");
    //jugar();
  }
}

void inicio()
{
  encenderTablero(255, 0, 0);
  delay(400);
  encenderTablero(0, 255, 0);
  delay(400);
  encenderTablero(0, 0, 255);
  delay(400);
  encenderTablero(255, 255, 0);
}
void setup() 
{
  randomSeed(analogRead(1));
  pinMode(PINVIBRADOR, OUTPUT);
  pinMode(PINMAGNETICO, INPUT);
  pinMode(PINRECOMPENSA, INPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {
  inicio();
  configurar();

}
