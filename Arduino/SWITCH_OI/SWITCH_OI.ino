#include <ESP8266.h>

#define SSID        "LabProto"
#define PASSWORD    "protocti2016"
#define HOST_NAME   "200.126.23.138"
#define HOST_PORT   (1880)

SoftwareSerial mySerial(3,2);
ESP8266 wifi(mySerial);

void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");

    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());

    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");

        Serial.print("IP:");
        Serial.println( wifi.getLocalIP().c_str());       
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    } else {
        Serial.print("single err\r\n");
    }
    
    Serial.print("setup end\r\n");
    pinMode(7,OUTPUT);
}
 
void loop(void)
{
    int val=digitalRead(7);
    if(val==1){
      uint8_t buffer[1024] = {0};
      Serial.print("Empieza");
      if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
          Serial.print("create tcp ok\r\n");
      } else {
          Serial.print("create tcp err\r\n");
      }
      char *hello = "GET /MODIFY/ACTION?ip=192.168.65.241 HTTP/1.1\r\nHost: 200.126.23.138\r\nConnection: close\r\n\r\n";
      wifi.send((const uint8_t*)hello, strlen(hello));
      if (wifi.releaseTCP()) {
          Serial.print("release tcp ok\r\n");
      } else {
          Serial.print("release tcp err\r\n");
      }
    }
}
     
