#define SSID       "Itead_1(Public)"
#define PASSWORD   "27955416"


#include "ESP8266.h"
#include <SoftwareSerial.h>
WIFI wifi;


void setup()
{
  
  wifi.begin();
  bool b = wifi.Initialize(STA, SSID, PASSWORD);
  if(!b)
  {
    DebugSerial.println("Init error");
  }
  delay(8000);  //make sure the module can have enough time to get an IP address 
  String ipstring  = wifi.showIP();
  DebugSerial.println("My IP address:");
  DebugSerial.println(ipstring);		//show the ip address of module
  
  String wifistring  = wifi.showJAP();
  DebugSerial.println(wifistring);  	//show the name of current wifi access port
  
}
void loop()
{
  

}
