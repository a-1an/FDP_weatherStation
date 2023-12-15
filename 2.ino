#include <Adafruit_Sensor.h>
#include <DHT11.h>

DHT11 dht11(D3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(2000);
  //read temperature and humidity
  float t = dht11.readTemperature();
  float h = dht11.readHumidity();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // print temperature
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");
  
  // print humidity
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}
