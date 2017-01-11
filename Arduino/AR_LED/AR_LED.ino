
#include "ESP8266.h"
#include "IRTemp.h"
#include <SoftwareSerial.h>

#define SSID        "CTI_DOMO"
#define PASSWORD    "ct1esp0l15"

#define HOST_NAME   "200.126.23.138"
#define HOST_PORT   1880

#define PERIOD 15 //How often to send data (in seconds)

SoftwareSerial mySerial(3,2); /* RX:D2, TX:D3 */
ESP8266 wifi(mySerial);

String head = "GET /update?api_key=";
String tail = "\r\n\r\n";
String command;

void setup(void) {
    Serial.begin(9600);
    Serial.print("setup begin\r\n");
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
    while(!wifi.setOprToStation()){
      Serial.print("to station + softap err\r\n");
    }
    Serial.print("to station + softap ok\r\n");
    while(!wifi.joinAP(SSID, PASSWORD)){
      Serial.println("Obteniendo ip..");
    }
    Serial.print("Join AP success\r\n");
    Serial.print("IP:");
    Serial.println( wifi.getLocalIP().c_str()); 
    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    } else {
        Serial.print("single err\r\n");
    }
    Serial.print("setup end\r\n");
}

void loop(void) {
  delay(1000);
}

void sendTemperature(float t,float t2)
{
  String field1,field2;
  field1 = "&field1=";
  field2 = "&field2=";
  if (!isnan(t)) {
    Serial.println("Enviando..");
    //command = head+key+field1+String(t,2)+field2+String(t2,2)+tail;
    //Serial.print("Sending: "+command);
    wifi.createTCP(HOST_NAME, HOST_PORT);
    const char * data = command.c_str();
    Serial.print(data);
    wifi.send((const uint8_t *) data, command.length());
    wifi.releaseTCP();
  }  
}

