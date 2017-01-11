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
int notas[]={3830,3400,3038,2864,2550,3964,2272,2028,1912};
int paleta[][3]={{255,0,0},{0,255,0},{0,0,255},{180,160,0},{80,80,0},{140,0,170}};



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
  int luces = 1 ;
  int vibracion = 1;
  int sonido = 1;

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
  int level_colores = 3;
  int cont_ronda = 0;

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
      for(int i =0; i < 9; i++)
      {
        if(sonido==1)
          tone(PINSPEAKER,notas[random(0,8)]);
        if(luces==1){ 
          int indice=random(0,5);
          encenderTablero(paleta[indice][0],paleta[indice][1],paleta[indice][2]);
          delay(150);
        }
      }
  }
  noTone(PINSPEAKER);
  digitalWrite(PINVIBRADOR,0);
  apagarTablero();
}

void colores() 
{
  level_colores = 3;
  int exit_flag = 1;
  int temp[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
  
 while(exit_flag||level_colores==7){
  if (level_colores == 7){
    // RECOMPENSA
    recompensar();
    level_colores = 3;
  }
  jtemp = 0;
  for(int i =0; i<9; i++){
    temp[i]=-1;
    }
  while (temp[level_colores-1]==-1)
  { // llena un arreglo temporal "temp" con RGBs no repetidos.
    randomRGB = random(0, 9);
    //Serial.println(randomRGB);
    int flag_repetido = 0;
    //Serial.println("random " + String(randomRGB));
    for(int k =0; k< level_colores; k++){
      if(temp[k]==randomRGB){
        flag_repetido = 1;
        break;
      }
    }
    if(!flag_repetido)
    {
        temp[jtemp]= randomRGB;
        jtemp++;
    }  
  }
  strSol = "";
  int flag = 0;
  for(int i = 0; i<9; i++){
    for(int j =0; j < level_colores-1;j++){
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
  for(int i = 0; i<9; i++)
  //Serial.print(temp[i]);

  Serial.println();
  //while (!(strLDR.substring(0,9)==strSol)) 
  while (!(strLDR.equals(strSol))) 
  {
    //delay(400);
    //Serial.println(strSol);
    //Serial.println(strLDR);
    //Serial.println("--------");
    strLDR = leerLDRs();
    
    int value_conf_estimulos =  analogRead(PINCONFESTIMULOS);
    for(int i =0; i<level_colores; i++)
    encenderRGB(groundPin[temp[i]], 0, 0, 255);
    encenderRGB(groundPin[temp[level_colores-1]], 255, 0,0);
    
    //exit_flag = menu(analogRead(PINMENU));
  }

  for(int i =0; i<3; i++){
    encenderRGB(groundPin[temp[level_colores-1]], 0, 0, 255);
    delay(150);
    encenderRGB(groundPin[temp[level_colores-1]], 255, 0, 0);
    delay(150);
  }
    apagarTablero();
    delay(500);
    cont_ronda++;
    if (cont_ronda==4){
      level_colores++;
      recompensar();
      cont_ronda = 0;
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

void configurarEstimulos(int value_conf_estimulos) {
  if (value_conf_estimulos < 94 && value_conf_estimulos > 80) {
        Serial.println("botón rojo");
        luces = 1;
        vibracion = 0;
        sonido = 0;
     }
     if (value_conf_estimulos < 514 && value_conf_estimulos > 505) {
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
}

void motricidad() {
  int intensidad=5;
  Serial.println("Entro");
  delay(1000);
  while (menu(analogRead(PINMENU))!=5){
    val = digitalRead(PINMAGNETICO);   // read the input pin
    if(val==0){
      Serial.println("Separados");
      if(intensidad<255)
          intensidad+=10;
      delay(250);
    }
    else{
       intensidad=5;
       Serial.println("Unidos");
    }
    analogWrite(PINVIBRADOR,intensidad);
  }
  analogWrite(PINVIBRADOR,0);
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
  analogWrite(PINVIBRADOR,0);
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
  recompensar();
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

void vistoyx()
{
  valorMenu=analogRead(PINMENU); 
  if(valorMenu>85 && valorMenu<95)
    recompensar();
  else if(valorMenu>670 && valorMenu<680){
      analogWrite(PINVIBRADOR,255);
      delay(1000);
      analogWrite(PINVIBRADOR,10);
  }
  delay(1000);
}

int menu(int valorMenu)
{
    Serial.println(valorMenu);
    if(valorMenu>170 && valorMenu<175){
        // boton1
        Serial.println("motricidad Magnetico");
        return 1;
    }
    else if(valorMenu>690 && valorMenu<695){
        // boton2
        Serial.println("imitación sonidos");
        return 2;
    }
    else if(valorMenu>925 && valorMenu<935){
        // boton3
       Serial.println("colores");
       return 3;
    }
    else if(valorMenu>670 && valorMenu<680){
        // boton4
        Serial.println("visto y la X");
        return 4;
    }
    else if(valorMenu>85 && valorMenu<95){
      // boton5
      Serial.println("volver al menú");
      return 5;
    }
    return 0;
}


void loop() {
  int valor_conf_estimulos,valor_menu,op,i=255;
  analogWrite(PINVIBRADOR,255);
  inicio();
  apagarTablero();
  analogWrite(PINVIBRADOR,0);
  while(true){
    valor_conf_estimulos=analogRead(PINCONFESTIMULOS);
    valor_menu=analogRead(PINMENU); 
    configurarEstimulos(valor_conf_estimulos);
    op=menu(valor_menu);
    switch(op){
      case 1:
        motricidad();
        break;
      case 2:
        musica();
        break;
      case 3:
        colores();
        break;
      case 4:
        vistoyx();
        break;
    }
  }
}


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


