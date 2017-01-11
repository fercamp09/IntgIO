#include <ESP8266.h>
#include <Servo.h>
#include <stdio.h>
#define SSID        "CTI_IOT"
#define PASSWORD    "protocti2016"

SoftwareSerial mySerial(3,2);
ESP8266 wifi(mySerial);

Servo myservo;

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
        Serial.print("IP: ");
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
    pinMode(7,OUTPUT);
    myservo.attach(9);
}
 
void loop(void)
{
    
    uint8_t buffer[128] = {0};
    uint8_t mux_id;
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Received from :");
        Serial.print(mux_id);
        Serial.print("[");
        String cad;
        for(uint32_t i = 0; i < len; i++) {
            char c;
            c=(char)buffer[i];
            Serial.print(c);
            cad=cad+c;
        }
        Serial.print("]\r\n");
        uint32_t indice=cad.indexOf("?VALUE:");
        indice=indice + 7;
//        char[] val = [];
        String val = cad.substring(indice,indice+2);
//        for(uint32_t i = indice; i < indice+3; i++){
//          val=val+cad[indice];
//          Serial.print(val);
//        }
        uint32_t val1;
        val1=val.toInt();
        Serial.print(val1);
        myservo.write(val1);
        if(wifi.send(mux_id, buffer, len)) {
            Serial.print("\nsend back ok\r\n");
        } else {
            Serial.print("\nsend back err\r\n");
        }
        
        if (wifi.releaseTCP(mux_id)) {
            Serial.print("release tcp ");
            Serial.print(mux_id);
            Serial.println(" ok");
        } else {
            Serial.print("release tcp");
            Serial.print(mux_id);
            Serial.println(" err");
        }
        
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
    }
}
    
