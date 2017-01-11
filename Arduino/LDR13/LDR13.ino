#include <RGB.h>
#include <Wire.h>
/*
   rojo - luces
   negro - vibración
   azul - sonido
*/
#define TOTALRGB 9
#define PINVIBRADOR 6
#define PINMAGNETICO A3
#define PINSPEAKER 5
#define PINCONFESTIMULOS A1
#define PINMENU A0
#define TIME_OUT  10

int speakerPin = 5, val, val2, time;
int notas[]={3830,3400,3038,2864,2550,2272,2028,1912};

String strLDR;
String strSol = "";
/*
 * PWM para colores
 */
int pinRojo = 11;
int pinVerde = 10;
int pinAzul = 9;

int valorMenu;
int value_conf_estimulos;
/*
 * Arreglo de pines para controlar LDRs
 */
int groundPin[TOTALRGB] = { 0, 1, 2, 3, 4, 7, 8, 12, 13};

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
    digitalWrite(groundPin[i], LOW);
  }
}

void encenderRGB(int pin, int rojo, int verde, int azul)
{
  for(int i = 0; i<TOTALRGB; i++){
     digitalWrite(groundPin[i], 0);
     setColor(0, 0, 0);
  }
  digitalWrite(pin, 1);
  setColor(rojo, verde, azul);
}

void acumularRGB(int pin, int rojo, int verde, int azul)
{
  digitalWrite(pin, 1);
  setColor(rojo, verde, azul);
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
  while (temp[2]==-1) 
  { // llena un arreglo temporal "temp" con RGBs no repetidos.
    randomRGB = random(0, 9);
    //Serial.println("random " + String(randomRGB));
    if (!(randomRGB==(temp[0])) && (!(randomRGB==(temp[1]))) && (!(randomRGB==(temp[2])))) {
      temp[jtemp] = randomRGB;
      jtemp++;
    }
  }
  tempRed = random(0,100);
  tempGreen = random(100,255);
  tempBlue = random(100,255);
  delay(200);
  Serial.println(temp[0]);
  Serial.println(temp[1]);
  Serial.println(temp[2]);
  strSol = "";
  int flag = 0;
  for(int i = 0; i<9; i++){
    for(int j =0; j < 3;j++){
        if (temp[j]== i){
          strSol+=0;
          flag = 1;
        }
      }
      if (flag == 1)
        flag =0;
      else
        strSol+=1;
  }
  strLDR = leerLDRs();
  Serial.println(strSol);
  while (!(strLDR.substring(0,9)==strSol)) 
  {
    strLDR = leerLDRs();
    Serial.println(strLDR);
    int value_conf_estimulos =  analogRead(PINCONFESTIMULOS);
    encenderRGB(groundPin[(temp[2])], 255, 0, 0);
    encenderRGB(groundPin[(temp[1])], 0, 255, 0);
    encenderRGB(groundPin[(temp[0])], 0, 255, 0);
    
    if (value_conf_estimulos > 927 && value_conf_estimulos < 945) {
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
    int value_conf_estimulos =  analogRead(PINCONFESTIMULOS);
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

    if (value_conf_estimulos > 927 && value_conf_estimulos < 945) {
      Serial.println(" ---- Recompensa");
      recompensar();
    }
    Serial.println(" ---- jugando");
  }
}

void configurar() {
  int value_conf_estimulos =  analogRead(PINCONFESTIMULOS);
  Serial.println(value_conf_estimulos);
  if (value_conf_estimulos < 94 && value_conf_estimulos > 80) {
    //Serial.println("botón rojo");
    luces = 1;
    vibracion = 0;
    sonido = 0;
  }
  else if (value_conf_estimulos < 514 && value_conf_estimulos > 510) {
    //Serial.println("botón negro");
    luces = 0;
    vibracion = 1;
    sonido = 0;
  }
  else if (value_conf_estimulos > 170 && value_conf_estimulos < 176) {
    //Serial.println("botón azul");
    luces = 0;
    vibracion = 0;
    sonido = 1;
  }
  else if (value_conf_estimulos > 237 && value_conf_estimulos < 241) {
    //Serial.println("rojo y azul");
    luces = 1;
    vibracion = 0;
    sonido = 1;

  }
  else if (value_conf_estimulos > 535 && value_conf_estimulos < 539) {
    //Serial.println("rojo y negro");
    luces = 1;
    vibracion = 1;
    sonido = 0;
  }
  else if (value_conf_estimulos > 579 && value_conf_estimulos < 582) {
    //Serial.println("todas");
    luces = 1;
    vibracion = 1;
    sonido = 1;
  }
  else if (value_conf_estimulos > 557 && value_conf_estimulos < 563) {
    //Serial.println("azul negro");
    luces = 0;
    vibracion = 1;
    sonido = 1;
  }
  else if (value_conf_estimulos > 927 && value_conf_estimulos < 945) {
    //while(value_conf_estimulos<929 || value_conf_estimulos>945);
    Serial.println(" ---- A jugar");
    //jugar();
  }
}

void motricidad() {
  int flag = 0;
  delay(1000);
  while (menu(analogRead(PINMENU),-1)){
    val = digitalRead(PINMAGNETICO);   // read the input pin
    digitalWrite(PINVIBRADOR, !val);    // sets the LED to the button's value 
    for(int i = 0; i<TOTALRGB; i++)
    {
      digitalWrite(groundPin[0], val);  
    }
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
  pinMode(PINMENU, INPUT);
  pinMode(PINCONFESTIMULOS, INPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  setupRGB();
  Wire.begin();
  //Serial.begin(9600);
}

void musica(){
  String LDRs;
  int patron1[]={},patron2[]={},k=0;
  do{
    LDRs=leerLDRs();
    val=unicoLDR(LDRs);
  }while(val==-1);
  time=0;
  val2=-1;
  while(time<TIME_OUT){
    if(val!=-1){
      time=0;
      if(val2!=val){
        patron1[k]=val;
        acumularRGB(groundPin[val],255,0,0);
        Serial.print(patron1[k]);
        k+=1;
      }
      tone(PINSPEAKER,notas[val]);
      val2=val;
    }
    else{
      time=time+1;
      delay(250);
      noTone(PINSPEAKER);
    }
    LDRs=leerLDRs();
    val=unicoLDR(LDRs);
  }
  apagarTablero();
  Serial.print(patron1[0]);
  Serial.print(patron1[1]);
  Serial.print(patron1[2]);
  for(int i=0;i<k;i++){
    encenderRGB(groundPin[patron1[i]],0,255,0);
    delay(300);
  }
  int in=0;
  while(in<k){
    encenderRGB(groundPin[patron1[in]],0,255,0);
    delay(200);
    apagarTablero();
    LDRs=leerLDRs();
    Serial.println(LDRs);
    val=unicoLDR(LDRs);
    if(val==patron1[in] && val!=-1){
      in+=1;
      tone(PINSPEAKER,notas[val]);
    }
    else{
      analogWrite(PINVIBRADOR,250);
      delay(200);
      analogWrite(PINVIBRADOR,10);
      noTone(PINSPEAKER);
    }
  }
  noTone(PINSPEAKER);
  delay(1000);
}


String leerLDRs(){
    String LDRs;
    Wire.requestFrom(8, 9);   
    while (Wire.available()) { 
      char c=Wire.read();
      LDRs +=c;   
    }
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
          return i;
      }
  }
  return -1;
}
int menu(int valorMenu, int value_conf_estimulos)
{
    if(valorMenu>170 && valorMenu<175){
    // boton1
    Serial.println("motricidad Magnetico");
    motricidad();
    }
    else if(valorMenu>690 && valorMenu<695){
    // boton2
    Serial.println("imitación sonidos");
    imitacion();
    }
    else if(valorMenu>930 && valorMenu<935){
    // boton3
    Serial.println("colore");
    colores();
    }

    else if(valorMenu>670 && valorMenu<680){
    // boton4
    Serial.println("visto y la X");
    vistoyx();
    }

    else if(valorMenu>85 && valorMenu<95){
    // boton5
    Serial.println("volver al menú");
    return 0;
    }
    
    
    if (value_conf_estimulos < 94 && value_conf_estimulos > 80) {
    Serial.println("botón rojo");
    luces = 1;
    vibracion = 0;
    sonido = 0;
  }
  else if (value_conf_estimulos < 514 && value_conf_estimulos > 505) {
    Serial.println("botón negro");
    luces = 0;
    vibracion = 1;
    sonido = 0;
  }
  else if (value_conf_estimulos > 170 && value_conf_estimulos < 176) {
    Serial.println("botón azul");
    luces = 0;
    vibracion = 0;
    sonido = 1;
  }
  else if (value_conf_estimulos > 237 && value_conf_estimulos < 241) {
    Serial.println("rojo y azul");
    luces = 1;
    vibracion = 0;
    sonido = 1;

  }
  else if (value_conf_estimulos > 530 && value_conf_estimulos < 539) {
    Serial.println("rojo y negro");
    luces = 1;
    vibracion = 1;
    sonido = 0;
  }
  else if (value_conf_estimulos > 570 && value_conf_estimulos < 582) {
    Serial.println("todas");
    luces = 1;
    vibracion = 1;
    sonido = 1;
  }
  else if (value_conf_estimulos > 557 && value_conf_estimulos < 563) {
    Serial.println("azul negro");
    luces = 0;
    vibracion = 1;
    sonido = 1;
  }
  return 1;
}

void vistoyx()
{
  delay(1000);
  while (menu(analogRead(PINMENU),-1)){

  }
}

void loop() {
  inicio();
  configurar();
  //colores();
  //inicio();
  //menu(analogRead(PINMENU),analogRead(PINCONFESTIMULOS));
  //Serial.println(analogRead(PINCONFESTIMULOS));
  musica();
  

  
  /*
  String str = leerLDRs();
  Serial.println(str);
  for (int i =0; i<9; i++){
    if( str.substring(i,i+1) == "0"){
    encenderRGB(groundPin[i], 255,0,0);
    Serial.println(i);
    }
   }
   */
}

