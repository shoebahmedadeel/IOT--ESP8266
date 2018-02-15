#include <WiFiClient.h>

#include <ESP8266WebServer.h>

const char *ssid = "Ur Wifi Name";

const char *password = "";

ESP8266WebServer server(80);

float pressLength_milliSeconds = 0; 
int optionOne_milliSeconds = 100; 
int optionTwo_milliSeconds = 2000; 
int longHorn =0; 
int shortHorn =0; 
String webString="";  // switch is connected to pin D6 in Wemos R1 ESP board 
int switchPin = D6; 
int buttonState; // variable to hold the button state 
int buttonPresses = 0;
String Horn="";

void handleRoot() { //Handler for the rooth path

server.send(200, "text/plain", "Hello world");

}

void startServer() { while (digitalRead(switchPin) == LOW ){
delay(100); //if you want more resolution, lower this number 
pressLength_milliSeconds = pressLength_milliSeconds + 100;

}//close while

//Option 2 - Execute the second option if the button is held for the correct amount of time 
if (pressLength_milliSeconds >= optionTwo_milliSeconds){ longHorn++; } 

//option 1 - Execute the first option if the button is held for the correct amount of time else 

if(pressLength_milliSeconds >= optionOne_milliSeconds){ shortHorn++;

Serial.println(shortHorn); //every time through the loop, we need to reset the pressLength_Seconds counter 
pressLength_milliSeconds = 0;

server.send(200, "text/plain", String((int)shortHorn)); }
} 
void setup() {
delay(1000);
pinMode(switchPin, INPUT_PULLUP); 
Serial.begin(115200); 
Serial.println();
Serial.print("Configuring access point...");
WiFi.softAP(ssid, password); IPAddress myIP = WiFi.softAPIP(); 
Serial.print("AP IP address: "); 
Serial.println(myIP);
server.on("/", handleRoot);

server.on("/Honks", startServer); // if you add this subdirectory to your webserver call, you get button Counts :)

server.begin(); 
Serial.println("HTTP server started");

}

void loop() {

server.handleClient();

}
