#include <dht11.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoWiFiServer.h>
#include <ArduinoJson.h>

#define DHT11PIN 2

dht11 DHT11;

const char *ssid = "JakNieTwojaToNieRuszaj";   //Wifi Network Name
const char *password = "JakaNazwaTakieHaslo";  //Wifi Network Key
String hostname = "temperatureMonitor";

float temperature = 0.0;

String greenstate = "off";  // state of green LED

String redstate = "off";  // state of red LED


WiFiServer server(88);
String header;

void setup() {
  pinMode(DHT11PIN, INPUT);
  Serial.begin(9600);
  connectToWifi();

  server.begin();


  Serial.println("IP address: ");

  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println();

  startServer();
  //readTemperature();

  delay(2000);
}

void startServer() {
  WiFiClient client = server.available();
  if (!client) return;
  Serial.println(F("New client"));
  while (client.available()) client.read();
  StaticJsonDocument<500> doc;
    int temperature = readTemperature();
    int humidity = readHumidity();

    // Add the value at the end of the array
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;

  Serial.print(F("Sending: "));
  serializeJson(doc, Serial);
  Serial.println();

  // Write response headers
  client.println(F("HTTP/1.0 200 OK"));
  client.println(F("Content-Type: application/json"));
  client.println(F("Connection: close"));
  client.print(F("Content-Length: "));
  client.println(measureJsonPretty(doc));
  client.println();

  // Write JSON document
  serializeJsonPretty(doc, client);

  // Disconnect
  client.stop();
}

float readTemperature() {
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
  return DHT11.temperature;
}

float readHumidity() {
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  return DHT11.humidity;
}

void connectToWifi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid, password);
  Serial.print("Connecting to wifi: ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to wifi: ");
  Serial.println(ssid);
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  Serial.print("Hostname: ");
  Serial.println(WiFi.hostname());
}