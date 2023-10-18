#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <iostream>
const char *ssid = "FiberHGW_ZTAT49_2.4GHz";
const char *password = "33khNYhCUeDf";
const char *server = "http://192.168.1.116:3000/deneyapkartRequest";
DynamicJsonDocument Leds(1024);
const int ledPins[6] = {D2, D3, D4, D5, D6, D7};
void connectWifi();
void getRequest(HTTPClient &client, const char *uri);
void setup()
{
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  for (int i = 0; i < 6; i++)
  {
    String ledObject = "{\"id\":" + String(i) + ",isOpen:false}";
    DynamicJsonDocument object(1024);
    deserializeJson(object, ledObject);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
    Leds[String(i)] = object;
  }
  Serial.begin(115200);
  connectWifi();
}

void loop()
{
  while (WiFi.status() != WL_CONNECTED)
  {

    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
  }
  HTTPClient http;
  delay(1000);
  getRequest(http, server);
}

void connectWifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LEDR, HIGH);
    Serial.print("Wi-Fi bağlantısı kuruluyor");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
  }
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  Serial.println("Wi-Fi bağlantısı kuruldu.");
}
void getRequest(HTTPClient &client, const char *uri)
{
  String ledsString;
  serializeJson(Leds, ledsString);
  client.begin(uri);
  client.addHeader("Content-Type", "application/json");
  int httpCode = client.POST(ledsString);
  if (httpCode > 0)
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, HIGH);
    String res = client.getString();
    DynamicJsonDocument jsonObject(1024);

    deserializeJson(jsonObject, res);
    // for (int i = 0; i < 6; i++)
    // {
    //   Serial.println(String(ledPins[i]));
    //   const char *id = jsonObject[String(i)]["id"];
    //   Serial.println(id);
    // }
    for (JsonPair keyValue : jsonObject.as<JsonObject>())
    {
      JsonObject ledObject = keyValue.value().as<JsonObject>();
      int id = ledObject["id"];
      bool isOpen = ledObject["isOpen"];
      // Serial.print("LED ID: ");
      // Serial.println(ledPins[id]);
      // Serial.print("Is Open: ");
      if (isOpen)
      {
        digitalWrite(ledPins[id], HIGH);
      }
      else
      {
        digitalWrite(ledPins[id], LOW);
      }
      Serial.println(isOpen ? "true" : "false");
    }
  }
  else
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
  }

  client.end();
  delay(250);
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
  }
}