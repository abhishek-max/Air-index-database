#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "Redmi4"; //Enter SSID
const char* password = "123456789"; //Enter Password
int measurePin = A0;
int ledPower = 10;
unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
int relay=5;//D1~GPIO5
ESP8266WebServer server(80);
void setup(void)
{ 
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
  digitalWrite(relay,HIGH);
  //server.on("/control",control);
  //server.begin(); //Start the server
}
void loop()
{
  HTTPClient http;
  //-----------------------------------------------------------------------------------------------------//
  String postData,station="off";
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured*(3300.0/1024.0);//mapping data according to voltage and resolution of pins
  dustDensity = calcVoltage;
  Serial.println(500);
  Serial.println(dustDensity);
  Serial.println(50);
  postData = "status=" + String(dustDensity) + "&station="+station ;
  http.begin("http://192.168.43.121:8000/datahandler/api/");// enter your server/pc ip here
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);
  String payload = http.getString();//Get the request response payload
  http.end();
  //---------------------------------------------------------------------------------------------------//
  HTTPClient http1;
  http1.begin("http://192.168.43.121:8000/datahandler/switch/");
  http1.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode1 = http1.POST("");
  String payload1 = http1.getString();
  http1.end();
  if(payload1=="on")
  digitalWrite(relay,LOW);
  else if(payload1=="off")
  digitalWrite(relay,HIGH);
  //server.handleClient();
  //---------------------------------------------------------------------------------------------------//
  delay(5000);
}
/**void control()
{
  if (server.hasArg("plain")== false)
  { //Check if body received
    server.send(200, "text/plain", "Invalid Request");
    return;
  }
      else
      {
      server.send(200, "text/plain", "Request Recieved");
      if(server.arg("status")=="off")
      {
      digitalWrite(relay,HIGH);
      }
      else if(server.arg("status")=="on"){
      digitalWrite(relay,LOW);}
      }
}**/
