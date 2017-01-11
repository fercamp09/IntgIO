#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID        "CTI_DOMO"
#define PASSWORD    "ct1esp0l15"

SoftwareSerial serial(3,2);
ESP8266 wifi(serial);

void setup(void)
{
    Serial.begin(9600);
    
    Serial.print("setup begin\r\n");

    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());
    
    while(!wifi.setOprToStation()){
      Serial.println("conectando....");
    }
    while(!wifi.joinAP(SSID, PASSWORD)){
      Serial.println("obteniendo IP...");
    }
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");       
    Serial.println(wifi.getLocalIP().c_str());
    Serial.print("setup end\r\n");
}

void loop(void)
{
}
