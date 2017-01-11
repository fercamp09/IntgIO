/**
 * \file
 *       ESP8266 RESTful Bridge example
 * \author
 *       Tuan PM <tuanpm@live.com>
 *       Fernando Campana
 */

#include <espduino.h>
#include <rest.h>

#define PIN_ENABLE_ESP 13
#define SSID  "LabProto"     
#define PASSWORD "protocti2016" 

#define HOST_NAME "api.thingspeak.com"

ESP esp(&Serial1, &Serial, PIN_ENABLE_ESP);

REST rest(&esp);

boolean wifiConnected = false;

// Flow sensor
volatile int NbTopsFan; // measuring the rising edges of the signal
float flow_rate;    // Flow rate L/H 
float total_liters=0;                                     
float total_flowed=0;
float subtotal_flowed=0;
int hallsensor = 2;    // The pin location of the sensor
float calibrationFactor = 7.5;

// Controlar tiempo para thingspeak
const unsigned long tiempoEspera = 15000; //15 segundos
unsigned long oldTime = 0;

void rpm ()     //This is the function that the interupt calls 
{ 
  NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
} 

void wifiCb(void* response)
{
  uint32_t status;
  RESPONSE res(response);

  if(res.getArgc() == 1) {
    res.popArgs((uint8_t*)&status, 4);
    if(status == STATION_GOT_IP) {
      Serial.println("WIFI CONNECTED");
     
      wifiConnected = true;
    } else {
      wifiConnected = false;
    }
    
  }
}

void setup() {
  Serial1.begin(19200);
  Serial.begin(19200);
  esp.enable();
  delay(500);
  esp.reset();
  delay(500);
  while(!esp.ready());

  Serial.println("ARDUINO: setup rest client");
  if(!rest.begin(HOST_NAME)) {
    Serial.println("ARDUINO: failed to setup rest client");
    while(1);
  }

  /*setup wifi*/
  Serial.println("ARDUINO: setup wifi");
  esp.wifiCb.attach(&wifiCb);

  esp.wifiConnect(SSID, PASSWORD);
  Serial.println("ARDUINO: system started");

  /*setup flow sensor*/
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  attachInterrupt(1, rpm, RISING); //and the interrupt is attached
}

void loop() {
  char response[266];
  esp.process();
  if(wifiConnected) {
    compute_flow();
    if ((millis() - oldTime) >= tiempoEspera){
      char buff[128];
      char str_flow[6], str_total[6], str_total_flowed[6];
      dtostrf(flow_rate, 4, 2, str_flow);
      dtostrf(subtotal_flowed, 4, 2, str_total);
      dtostrf(total_flowed, 4, 2, str_total_flowed);
      sprintf(buff, "/update?api_key=X63QIA89E77GV6E8&field1=%s&field2=%s&field3=%s", str_flow, str_total, str_total_flowed);
      Serial.println(buff);
      rest.get((const char*)buff);
      Serial.println("ARDUINO: send get");
      oldTime = millis();
      subtotal_flowed = 0; 
    } 
  }
}

void compute_flow(){
  NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
  sei();      //Enables interrupts
  delay (1000);   //Wait 1 second
  cli();      //Disable interrupts
  flow_rate = (NbTopsFan * 60 / calibrationFactor); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour 
  Serial.print (flow_rate, DEC); //Prints the number calculated above
  Serial.print (" L/hour\r\n"); //Prints "L/hour" and returns a  new line
  total_liters = (NbTopsFan / (calibrationFactor * 60)); //Mililiters
  Serial.print (total_liters, DEC); //Prints the number calculated above
  Serial.print (" L\r\n"); //Prints "L/hour" and returns a  new line
  subtotal_flowed += total_liters;
  total_flowed += total_liters;
  Serial.print (total_flowed, DEC); //Prints the number calculated above
  Serial.print (" L\r\n"); //Prints "L/hour" and returns a  new line
}


