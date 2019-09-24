
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
 
// Wifi credentials 
const char *ssid = "ssid";  
const char *password = "password";
String server_url = "http://enter-your-server-name.net";
 

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);     
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}
 
void loop() {
  HTTPClient http;   
 
  String WeatherData_temp, station, data_uri, server_url;
  int value=analogRead(A0);  // temperature reading
  WeatherData_temp = String(value);   
 
   //Send Data to server
   data_uri = "?temp=" + WeatherData_temp;   // encode data in url
   get_url = server_url + "/api/my/status" + data_uri;
   post_url = server_url + "/api/my/weather";
  
  http.begin(post_url);     //Specify request destination
  
  int httpCode = http.POST("{ \"temperature\" :" + WeatherData_temp + "}"); // sending JSON       
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end(); 
  
  delay(5000);  //5 seconds later
  
  http.begin(get_url);     //Specify request destination
  
  int httpCode = http.GET(); // send url encoded request      
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end(); 
}
