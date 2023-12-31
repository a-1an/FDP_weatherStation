#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_Sensor.h>
#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const char* ssid = "OPPO";
const char* password = "blynk1234";
String serverUrl = "http://api.openweathermap.org/data/2.5/weather?q=KOCHI&appid=7f29f73f56a4c0e81cbdd4900b8886bb";

const int touchSensorPin = D6; // Change this to the pin connected to your touch sensor

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT11 dht11(D3);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

unsigned long lastTime = 0;
unsigned long timerDelay = 5000; // 15 seconds
bool displayWeather = false;
int displayCount = 0;
bool touchTriggered = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Wire.begin();
  display.begin(i2c_Address, true);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  pinMode(touchSensorPin, INPUT);
  timeClient.begin();
  timeClient.setTimeOffset(19800); // Set your timezone offset in seconds (19800 is for IST)
}

void loop() {
  timeClient.update();
  if (digitalRead(touchSensorPin) == HIGH) {
    touchTriggered = true;
    displayCount = 0;
  }
  if ((millis() - lastTime) > timerDelay && touchTriggered) {
    display.clearDisplay();
    if (displayCount < 2) {
      float t = dht11.readTemperature();
      float h = dht11.readHumidity();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.print("Temperature: ");
      display.setTextSize(2);
      display.setCursor(0,10);
      display.print(t);
      display.print(" C");
      display.display();
      display.setTextSize(1);
      display.setCursor(0,35);
      display.print("Humidity: ");
      display.setTextSize(2);
      display.setCursor(0,45);
      display.print(h);
      display.print(" %");
      display.display();
      delay(timerDelay);
      display.clearDisplay();
      if(WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, serverUrl.c_str());
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
          String payload = http.getString();
          StaticJsonDocument<1024> doc;
          DeserializationError error = deserializeJson(doc, payload);
          if (!error) {
            JsonObject weather_0 = doc["weather"][0];
            const char* weather_main = weather_0["main"];
            const char* weather_description = weather_0["description"];
            display.setTextSize(1);
            display.setCursor(0,0);
            display.print("Weather: ");
            display.setTextSize(2);
            display.setCursor(0,10);
            display.print(weather_main);
            display.setTextSize(1);
            display.setCursor(0,35);
            display.print("Description: ");
            display.setTextSize(2);
            display.setCursor(0,45);
            display.print(weather_description);
            display.display();
            delay(timerDelay);
          }
        }
        http.end();
      }
    }
    displayCount++;
    if (displayCount >= 2) {
      touchTriggered = false;
    }
    lastTime = millis();
  } else {
    display.display();
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,10);
    display.print("Time: ");
    display.setTextSize(2);
    display.setCursor(0,35);

    int hour = timeClient.getHours(); // get the hour in 24-hour format
    String am_pm = "AM";

    if(hour >= 12) {
      if(hour > 12) hour = hour - 12;
          am_pm = "PM";
        }
       if(hour == 0) {
        hour = 12;
        }

        // Now 'hour' contains the time in 12-hour format and 'am_pm' contains either "AM" or "PM"
         String time_str = String(hour) + ":" + String(timeClient.getMinutes()) + " " + am_pm;

          display.print(time_str);
          display.display();

  }
}
