#include <ESP8266.h>

#define SSID        "CTI_IOT"
#define PASSWORD    "protocti2016"
#define HOST_NAME   "200.126.23.138"
#define HOST_PORT   (1880)

SoftwareSerial mySerial(3,2);
ESP8266 wifi(mySerial);

int potpin = 0;
int val;
int valPast=-1;

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
  delay(15);  
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 160);
  if (valPast != val){
    Serial.print(val);
    valPast = val;
  }
}
     
