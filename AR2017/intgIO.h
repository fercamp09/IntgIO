// Change this if the filenames are changed
#ifndef INTGIO_h
#define INTGIO_h
#include "application.h"
// This #include statement was automatically added by the Particle IDE.
#include <HttpClient.h>
// Library for MQTT client
#include <MQTT.h>
// RGB LED
#define COMMON_ANODE                                       // common anode rgb led

class IntgIO {
    private:
        // HTTP Client
        HttpClient http;
        http_request_t request;
        http_response_t response;
        
        // Codes
        String devcode = "photon3";
        
        String actPot = "movePot3";
        String objPot = "pot3";
        
        String actServo = "moveServo3";
        String objServo = "servo3";

        String actLEDONOFF = "turnOnOff3";
        String actLEDColor = "changeColor3";
        String objled      = "led3";
        
        String actSwitch = "sendSignal3";
        String objSwitch = "switch3";
        
        
        // intgIO Server
        String hostname = "200.126.23.138"; //
        int portHost    = 1883; //
        
        // Wi-fi Credentials
        const String SSID     = "CTI_IOT";    
        const String PASSWORD = "";                      // Replace with real password 
        
        // TCP Server definition
        const int TCPPORT  = 80;
        TCPServer server   = TCPServer(TCPPORT);
        TCPClient client;
        bool wifiConnected = false;
        
        // MQTT
        //MQTT mqttClient;         // MQTT Client initialization
        const String BROKER = "200.126.23.131";
        const int PORT      = 1883;
        const String USER   = "james";
        const String PASS   = "";                   // Replace with real password 
        MQTT mqttClient;          // MQTT Client initialization
        
        // LED pins
        const int REDPIN = D2;
        const int GREENPIN = D1;
        const int BLUEPIN = D0;
        int red;
        int green;
        int blue;
        
        // Potentiometer
        int POTPIN = A0;
        float valPot = 0.0;
        int prevValPot = 0;
        
        // Servo
        int SERVOPIN = A4;
        float valServo = 0.0;
        Servo myServo;
        
        // Button 
        int BUTTONPIN = D3;     // the number of the pushbutton pin
        int buttonState = 0;          // variable for reading the actual button status
        int prevbuttonState = 0;      // variable for holding the previous button status
        //bool pressed = false;       // variable for reading the pushbutton status
        bool on = false;              // variable for reading the pushbutton status
        
        // Light Sensor
        
        // Variables for holding actions info
        String* globalActions;
        float* globalStatuses;
        String* globalTypes;
        int globalSize;
        
        // Received buffer
        String receivedMsg = "";
        int recMsgOffset = 0;
        String codeActionStr = String("");
        String statusActionStr = String("");
    public:
      IntgIO(String code);
      String getDeviceID();
      void updateAction(String action, float value);
      void updateActions(String actions[], float values[], int size);
      void executeAction(String action, float value);
      // TCP
      void listenTCPServer();
      // MQTT
      void listenMQTTClient(MQTT mqttClient);
      void subscribe(String action);
      void mqttCallback(char* topic, byte* payload, unsigned int length);
      // Potentiometer
      void addPotentiometer(String objCode, String actCode);
      void addPotentiometer(String objCode, String actCode, int pin);
      void movePotenciometer();
      String getPotentiometerAction();
      // Servo
      void addServo(String objCode, String actCode);
      void addServo(String objCode, String actCode, int pin);
      void moveServo(float value);
      String getServoAction();
      // LED 
      void turnLedRGBOnOff();
      void turnLedOnOff();
      void setColor(int red, int green, int blue);
      void changeColor(float value, int * color);
      // Switch
      void turnOnOff(float value);
      // Auxiliary methods
      float map0_1(float x, float in_min, float in_max);
      float floatMap(float x, float in_min, float in_max, float out_min, float out_max);
      
};

class Light{
    
};

class LightSensor{
    
};

class Button{
    
};

#endif
