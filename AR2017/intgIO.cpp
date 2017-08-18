// Change this if the filenames are changed
#ifndef INTGIO_cpp
#define INTGIO_cpp
#include "intgIO.h"


/////////////////////////////////////////////////////////////// Variables ///////////////////////////////////////////////////////////////////////////////////

/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * MQTT client("www.sample.com", 1883, callback);
 **/
// MQTT
        
//////////////////////////////////////////////////////////////// Program //////////////////////////////////////////////////////////////////////////////////
// Function run first when device turns on

IntgIO::IntgIO(String code){
    // Start serial  
    // Serial.begin(9600);
    
    // Set device code
    devcode = code;
    
    // Initialize the leds pins as inputs
    //pinMode(REDPIN, OUTPUT);
    //pinMode(GREENPIN, OUTPUT);
    //pinMode(BLUEPIN, OUTPUT);  
      
    // initialize the pushbutton pin as an input:
    //pinMode(BUTTONPIN, INPUT);
      
    //setColor(0, 0, 0);
      
    // Setup wifi
    WiFi.setCredentials(SSID, PASSWORD);
    // For processing the credentials and connecting to the internet
    // while(!Serial.available()) 
    Particle.process();
    
    // Start listening for clients in the HTTP server
    server.begin();
    // Start MQTT client
    //MQTT mqttClient(BROKER, PORT, mqttCallback);          // MQTT Client initialization
    //mqttClient.connect(devcode, USER, PASS);
    // Set info for request
    request.hostname = hostname;
    request.port = portHost;
    request.path = "/UPDATE/DEVICEON?code="+ devcode + "&ip="+ WiFi.localIP().toString() + "&puerto=" + TCPPORT + "&online=true";
    
    // Send GET request
    http.get(request, response);
    //Serial.print("Application>\tResponse status: ");
    //Serial.println(response.status);
    // Obtain response
    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);
    String body = response.body;
    // Get info from response
    int offset = body.lastIndexOf(",");
    Serial.print("offset: ");
    Serial.println(offset);
    offset++;
    
    // Get number of actions
    int length = 0;
    String lengthString = String("");
    while(93 != body.charAt(offset)){ // 93 is ASCII for ]
        Serial.print("offset: ");
        Serial.println(offset);
        lengthString.concat(body.charAt(offset));
        offset++;
    }
    
    length = lengthString.toInt();
    Serial.print("length: ");
    Serial.println(length);
    
    // Variables for holding actions info
    String actions[length];
    float statuses[length];
    String types[length];
    
    offset = 1;
    int i = 0;
    while(-1 != body.indexOf("[", offset)){
        offset = body.indexOf("[", offset);
        offset = offset + 2; // for the "\"", 34 in ASCII
        Serial.print("offset: ");
        Serial.println(offset);
        
        // Searching for the code
        String codeString = String("");
        while(34 != body.charAt(offset)){
            Serial.print("offset: ");
            Serial.println(offset);
            
            codeString.concat(body.charAt(offset));
            offset++;
        }
        Serial.print("code: ");
        Serial.println(codeString);
        actions[i] = codeString;
        
        offset = offset + 3; // for the comma "," and next "\""
        
        // Searching for the status
        String statusString = String("");
        float status = 0.0;
        
        while(34 != body.charAt(offset)){ // 44 is "," in ASCII, 34 is "\"" in ASCII
            statusString.concat(body.charAt(offset));
            offset++;
        }
        status = statusString.toFloat();
        statuses[i] = status;
        Serial.print("status: ");
        Serial.println(statusString);
        Serial.println(status);
        
        offset = offset + 2; // for the comma "," and next "\""
        
        // Searching for the type
        String typeString = String("");
        while(34 != body.charAt(offset)){
            Serial.print("offset: ");
            Serial.println(offset);
            
            typeString.concat(body.charAt(offset));
            offset++;
        }
        Serial.print("type: ");
        Serial.println(typeString);
        types[i] = typeString;
        
        // For advancing the array
        i++;
    }
    // Get available actions from server and put them in an array, for updating
    
    //globalActions = actions;
    //globalStatuses = statuses;
    //globalTypes = types;
    globalSize = length;
    
    // Update actions with the actual status of the actions in this device
    updateActions(actions, statuses, globalSize);
    
    //red = 255;
    //green = 255;
    //blue = 255;
}

///////////////////////// Potentiometer //////////////////////////////////

void IntgIO::addPotentiometer(String objCode, String actCode){
    objPot = objCode;
    actPot = actCode;
    prevValPot = valPot;
}

void IntgIO::addPotentiometer(String objCode, String actCode, int pin){
    objPot = objCode;
    actPot = actCode;
    POTPIN = pin;
    prevValPot = valPot;
}

void IntgIO::movePotenciometer(){
    valPot = analogRead(POTPIN);    // read the value from the sensor
    valPot =  map0_1(valPot, 0.0, 4095.0);
    changeColor(valPot, &green);
  
    int intPot = valPot * 100;
    if (intPot != prevValPot){ 
        executeAction(actPot, valPot);
    }
    delay(100);
    prevValPot = intPot; 
}

String IntgIO::getPotentiometerAction(){
    return actPot;
}

////////////////////////// Servo ////////////////////////////////////////

void IntgIO::addServo(String objCode, String actCode){
    objServo = objCode;
    actServo = actCode;
}

void IntgIO::addServo(String objCode, String actCode, int pin){
    objServo = objCode;
    actServo = actCode;
    SERVOPIN = pin;
}

void IntgIO::moveServo(float value){
    value = floatMap(value, 0.0, 1.0, 0, 159); ///////////////////////////////////////////
    myServo.write(value);
    delay(1);
}

String IntgIO::getServoAction(){
    return actServo;
}

  // Read the state of the pushbutton value:
  /*buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && prevbuttonState == LOW ) {
    pressed = !pressed;
  }
  // Check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (pressed) {
    // Turn LED on:
    setColor(255, 0, 0);  // red
    delay(500);
    // Send get update/actions once
    pressed = !pressed;
    request.hostname = hostname;
    request.port = port;
    request.path = "/MODIFY/ACTION3?code="+ actSwitch +"&value=1";
    //request.path = "/MODIFY/ACTION2?code="+ objSwitch +"&value=1";
    http.get(request, response);
  } else {
    // Turn LED off:
    //setColor(0, 0, 0);  // black
  }
  prevbuttonState = buttonState;
  */
  
// Turns on/off the RGB LED mantaining its colors
void IntgIO::turnLedRGBOnOff(){  
  if (on){
    setColor(red, green, blue);  // white
  }else{
    setColor(0, 0, 0);  // black
  }
}

// Turns on/off the LED
void IntgIO::turnLedOnOff(){  
  if (on){
    digitalWrite(GREENPIN, HIGH); 
  }else{
    digitalWrite(GREENPIN, LOW); 
  }
}

// Turns on/off 
void IntgIO::turnOnOff(float value)
{
    if (value < 0.1){
        on = false;
    } else {
        on = true;
    }
    //on = booleanMap(value, 0.0, 1.0, false, true);
}

void IntgIO::listenMQTTClient(MQTT mqttClient){
  // MQTT Loop
  if (mqttClient.isConnected())
        mqttClient.loop();
}

void IntgIO::listenTCPServer(){
  // TCP Server Loop
  if (client.connected()) {
    // echo all available bytes back to the client  
    recMsgOffset = 0;
    receivedMsg = "";
    
    while (client.available()) {
      // Obtain response
      char c = char(client.read());
      Serial.print(c);
      receivedMsg = receivedMsg + c; 
      server.write("\n");
    }
    // Send GET request (pull) but dont see  as necessary
    recMsgOffset = receivedMsg.indexOf("{");
      
    Serial.print("offset: ");
    Serial.println(recMsgOffset);
    recMsgOffset++;
      
    // Searching for the action code
    while(44 != receivedMsg.charAt(recMsgOffset)){ // 44 is "," in ASCII
         Serial.print("offset: ");
         Serial.println(recMsgOffset);
           
         codeActionStr.concat(receivedMsg.charAt(recMsgOffset));
         recMsgOffset++;
    }
    Serial.print("action code: ");
    Serial.println(codeActionStr);
      
    // Searching for the action status
    //statusActionStr = String("");
    recMsgOffset++;
    while(125 != receivedMsg.charAt(recMsgOffset)){ // 125 is "}" in ASCII
         Serial.print("offset: ");
         Serial.println(recMsgOffset);
           
         statusActionStr.concat(receivedMsg.charAt(recMsgOffset));
         recMsgOffset++;
    }
    Serial.print("action status: ");
    Serial.println();
    
    // Update status of actions
    updateAction(codeActionStr, statusActionStr.toFloat());
    Serial.println(receivedMsg);
  } else {
    // if no client is yet connected, check for a new connection
    client = server.available();
  }
}
 // recieve message
/*void IntgIO::mqttCallback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);
    String topic2(topic);
    float value = message.toFloat();
    if (topic2.indexOf(devcode) != -1){    
        updateAction(topic2, value);
        /*Serial.print("value:");
        Serial.println(value);
        Serial.print("red:");
        Serial.println(red);*/
    /*}
}*/

void IntgIO::setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    int red1 = 255 - red;
    int green1 = 255 - green;
    int blue1 = 255 - blue;
  #endif
    /*Serial.print("Color1:");
    Serial.print("redi:");
    Serial.println(red);
    Serial.print("greein:");
    Serial.println(green);*/
    analogWrite(REDPIN, red1);
    analogWrite(GREENPIN, green1);
    analogWrite(BLUEPIN, blue1);  
}


// Change only the selected color
void IntgIO::changeColor(float value, int * color)
{
    int val = floatMap(value, 0.0, 1.0, 0, 255);
    *color = val;
    Serial.println( *color);
    //setColor(red, green, blue);
} 

// Update the action state based on a name
void IntgIO::updateAction(String action, float value){
    if (action.indexOf(actLEDONOFF) != -1 || action.indexOf(actLEDColor) != -1){
        turnOnOff(value);
    //} else if (action.indexOf(actLEDColor) != -1){
        changeColor(value, &red);
    } else if (action == actPot){
        
    } else {
        Serial.println(action);
    }
    ////////////////////////////TO DO/////////////////////////////////////
    
    // Use a callback to execute each function when the action is detected
}

/*void IntgIO::registerAction(String action, float value){
    
}*/

// Update all actions states given a value
void IntgIO::updateActions(String actions[], float values[], int size){
    for (int i = 0; i < size; i++ ){
        /*Serial.println("value:");
        Serial.println(values[i]);
        Serial.println("action:");
        Serial.println(actions[i]);*/
        updateAction(actions[i], values[i]);
        subscribe(actions[i]);
    }
}

void IntgIO::subscribe(String action){
    mqttClient.subscribe(devcode+"/"+action);
}

// Maps data between 0 and 1
float IntgIO::map0_1(float x, float in_min, float in_max) {
    if (x > in_max) x = in_max;
    if (x < in_min) x = in_min;

    float out_min = 0.0;
    float out_max = 1.0;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Maps data for float values
float IntgIO::floatMap(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

String IntgIO::getDeviceID(){
    return devcode;
}

void IntgIO::executeAction(String action, float value){
    request.hostname = hostname;
    request.port = portHost;
    request.path = "/MODIFY/ACTION3?code=" + action + "&value=" + value;
    http.get(request, response);
}

#endif
