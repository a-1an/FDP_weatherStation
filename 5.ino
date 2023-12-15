#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "realmegt";
const char* password = "gt123abc";

String serverUrl = "http://api.openweathermap.org/data/2.5/weather?q=KOCHI&appid=7f29f73f56a4c0e81cbdd4900b8886bb";
int i=0;
unsigned long lastTime = 0;
unsigned long timerDelay = 300000;
char* input;
size_t inputLength;
String payload;
void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  if (i==0 || ((millis() - lastTime) > timerDelay) ){
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverUrl;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
  
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
        //Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        //Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
      i=1;
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      
      JsonObject weather_0 = doc["weather"][0];
      const char* weather_main = weather_0["main"]; // "Clouds"
      const char* weather_description = weather_0["description"]; // "overcast clouds"
      const char* weather_icon = weather_0["icon"]; // "04d"
      Serial.println(weather_main);
      Serial.println(weather_description);
      
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
