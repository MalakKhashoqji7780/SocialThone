
 #include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// Wi Fi Setup 
char ssid[] = "Majdi fiber 4g"; //your Wi-Fi name
char password[] = "0505306426";
 int ledPin = 2; // D4
  int ledPin2 = 0;//D3
   int ledPin3 = 16;//D2 
 int butnApin = 12; //d6
 int btnBpin = 14; // d5
 int btnCpin = 13; //7
  int btnDpin = 5;//1
  String dhtData;
  String Sleep = "I'm Sleepy";
  String Pain = "I'm hurt";
  String Water = "I need Water";
  boolean ledState = false;
  ESP8266WebServer server(80);
void handleRoot() { 
  // try typing your ip adress in your browser to check your connection
  server.send(200, "text/html", "<h1>connected</h1>");
}
  
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   
    }
   
 WiFi.mode(WIFI_STA);
 //add your IP adress
 //192.168.1.41
  IPAddress ip(192, 168, 1, 41);
  // if your are using macr OS: use this command in your terminal to get the ip adress: ipconfig getifaddr en0
  // if ypur are using windows OS: use this command in your cmd to get the ip adress: ipconfig
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
   
  server.on("/", handleRoot);
   server.on("/dht", sendDhtData);
    //server.on("/led/off", turnOffLed);
  server.begin();
pinMode(ledPin, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(butnApin, INPUT_PULLUP);
pinMode(btnBpin, INPUT_PULLUP);
pinMode( btnCpin, INPUT_PULLUP);
pinMode( btnDpin, INPUT_PULLUP);

}
void sendDhtData() {
  server.send(200, "text/plain", dhtData);
}
void turnOffLed() {
  ledState = false;
  digitalWrite(ledPin, ledState);
  server.send(200, "text/plain", "on");

}


void loop() {
// Button A for Blue LED, or LED Number 1 
server.handleClient();
if (digitalRead(butnApin)== LOW ){
 
  digitalWrite(ledPin, HIGH );
 
  if (digitalRead(ledPin)== HIGH && digitalRead(butnApin)== HIGH){
    Serial.println(Water);
      dhtData =  Water;
    }
  
  
  
  }
  

   
  // Button C for RED LED, or LED Number 2

  if (digitalRead(btnCpin)== LOW){
  digitalWrite(ledPin2, HIGH);
 if (digitalRead(ledPin2)== HIGH ){
    Serial.println(Pain);
    dhtData =  Pain;
    }
  

  
  }
  // Button D for Yalllow LED, or LED Number 1 

   if (digitalRead(btnDpin)== LOW){
  digitalWrite(ledPin3, HIGH);
   if (digitalRead(ledPin3)== HIGH  ){
    Serial.println(Sleep);
      dhtData =  Sleep;
    }

  }
  
  // Closing All LEDS
  if (digitalRead(btnBpin)== LOW){
  digitalWrite(ledPin, LOW);
   digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }




 
  
}
