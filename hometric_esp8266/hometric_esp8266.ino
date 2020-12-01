#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <ArduinoJson.h>
#define DHTTYPE DHT11
uint8_t DHTPin = D2;
DHT dht(DHTPin, DHTTYPE);

const char* ssid = "YOUR_SSID_HERE";
const char* password = "YOUR_PASS_HERE";
const char *serverName = "http://hometric.herokuapp.com/api/sensors/data";
unsigned long lastTime = 0;
unsigned long timerDelay = 60000;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  delay(100);
  pinMode(DHTPin, 2);
  dht.begin();
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 1 minute (timerDelay variable), it will take 1 minute before publishing the first reading.");
}

void loop()
{
  //Send an HTTP POST request every 5s
  if ((millis() - lastTime) > timerDelay)
  {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(h) || isnan(t))
    {
      Serial.println("Error obteniendo los datos del sensor DHT11");
      return;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      StaticJsonDocument<200> _data;
      _data["sensorName"] = "DHT11";

      JsonArray data = _data.createNestedArray("measures");

      StaticJsonDocument<200> _temp;
      _temp["name"] = "Temperature";
      _temp["value"] = t;
      _temp["units"] = "Celsius";
      StaticJsonDocument<200> _humidity;
      _humidity["name"] = "Humidity";
      _humidity["value"] = h;
      _humidity["units"] = "%";

      data.add(_temp);
      data.add(_humidity);

      String _json;
      serializeJson(_data, _json);

      int httpResponseCode = http.POST(_json);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
