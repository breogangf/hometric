#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "YOUR_SSID_HERE";
const char* password = "YOUR_PASS_HERE";
const char* serverName = "http://hometric.herokuapp.com/api/sensors/data";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  delay(50);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 5s
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
      //TODO retrieve DHT11 measures
      //TODO Add JSON Serializer
      int httpResponseCode = http.POST("{\n    \"sensorName\": \"DHT11\",\n    \"measures\": [\n        {\n            \"name\": \"Temperature\",\n            \"value\": 22.0,\n            \"units\": \"Celsius\"\n        },\n        {\n            \"name\": \"Humidity\",\n            \"value\": 56,\n            \"units\": \"%\"\n        }\n    ]\n}");
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload); 
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
