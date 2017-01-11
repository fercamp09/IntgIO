#include <ESP8266.h>

#define SSID        "LabProto"
#define PASSWORD    "protocti2016"

SoftwareSerial mySerial(3,2); /* RX:D2, TX:D3 */
ESP8266 wifi(mySerial);

#define HOST_NAME   "200.126.23.138"
#define HOST_PORT   1880

String head = "GET /";
String tail = " HTTP/1.1\r\n\r\n";
String command = "";
int sw = 7;
void setup(void)
{
    pinMode(sw,OUTPUT);
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
        Serial.print("Join AP success to: \r\n");        
        Serial.println(wifi.getLocalIP().c_str());    
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }
    
    if (wifi.startTCPServer(8090)) {
        Serial.print("start tcp server ok\r\n");
    } else {
        Serial.print("start tcp server err\r\n");
    }
    
    if (wifi.setTCPServerTimeout(10)) { 
        Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
    }
    
    Serial.print("setup end\r\n");
}
 
void loop(void)
{
    int val;
    String ip;
    val=digitalRead(sw);
    if(val==1){
      ip=wifi.getLocalIP().c_str();
      ip=ip.substring(13,27);
      sendAction(ip);
    }
}


void sendAction(String ip)
{
  String field;
  field = "MODIFY/ACTION?ip=";
  if (ip!=NULL){
    Serial.println("Enviando..");
    command = head+field+ip+tail;
    Serial.print(command);
    wifi.createTCP(HOST_NAME, HOST_PORT);
    const char * data = command.c_str();
    wifi.send((const uint8_t *) data, command.length());
    wifi.releaseTCP();
  }  
}
