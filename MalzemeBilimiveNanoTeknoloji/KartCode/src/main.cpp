/*
###### Enes AKTAŞ #########
###### 21.10.2023 #########
###### PlatformIO Linux ###
*/
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <iostream>
const char *ssid = "deneyapGebze";
const char *password = "deneyap11";
const char *ssid1 = "DENEYAP 2";
const char *password1 = "deneyap22";
const char *ssid2 = "FiberHGW_ZTAT49_2.4GHz";
const char *password2 = "33khNYhCUeDf";
const char *server = "https://mlzmblmvnntknljprjsrv.senesatka.repl.co/deneyapkartRequest";
HTTPClient http;

DynamicJsonDocument Leds(1024);
const int ledPins[6] = {D2, D3, D4, D5, D6, D7};
int ledStates[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
const int piezoPins[3] = {A0, A1, A2};
void connectWifi();
void getRequest(HTTPClient &client, const char *uri);
void piezoLedsControl();
void setup()
{
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(A0, INPUT);
  for (int i = 0; i < 6; i++)
  {
    String ledObject = "{\"id\":" + String(i) + ",isOpen:false}";
    DynamicJsonDocument object(1024);
    deserializeJson(object, ledObject);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
    Leds[String(i)] = object;
  }
  for (int i = 0; i < 3; i++)
  {
    pinMode(piezoPins[i], INPUT);
  }
  Serial.begin(115200);
  connectWifi();
}

void loop()
{
  piezoLedsControl();
  if (WiFi.status() == WL_CONNECTED)
    getRequest(http, server);
}
void piezoLedsControl()
{
  int piezo1State = map(analogRead(A0), 8191, 0, 100, 0);
  int piezo2State = map(analogRead(A1), 8191, 0, 100, 0);
  int piezo3State = map(analogRead(A2), 8191, 0, 100, 0);
  int piezoLimit[3] = {50, 50, 50};
  Serial.print("1: ");
  Serial.println(piezo1State);
  Serial.print("2: ");
  Serial.println(piezo2State);
  Serial.print("3: ");
  Serial.println(piezo3State);
  if (piezo1State > piezoLimit[0])
  {
    ledStates[0] = HIGH;
    ledStates[3] = HIGH;
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[3], HIGH);
  }
  if (ledStates[0] != HIGH)
  {
    ledStates[0] = LOW;
    digitalWrite(ledPins[0], LOW);
  }
  if (ledStates[3] != HIGH)
  {
    ledStates[3] = LOW;
    digitalWrite(ledPins[3], LOW);
  }
  if (piezo2State > piezoLimit[1])
  {
    ledStates[1] = HIGH;
    ledStates[4] = HIGH;
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[4], HIGH);
  }
  if (ledStates[1] != HIGH)
  {

    ledStates[1] = LOW;
    digitalWrite(ledPins[1], LOW);
  }
  if (ledStates[4] != HIGH)
  {
    ledStates[4] = LOW;
    digitalWrite(ledPins[4], LOW);
  }
  if (piezo3State > piezoLimit[2])
  {
    ledStates[2] = HIGH;
    ledStates[5] = HIGH;
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[5], HIGH);
  }
  if (ledStates[2] != HIGH)
  {
    ledStates[2] = LOW;
    digitalWrite(ledPins[2], LOW);
  }
  if (ledStates[5] != HIGH)
  {
    ledStates[5] = LOW;
    digitalWrite(ledPins[5], LOW);
  }
}
void connectWifi()
{
  byte ssidNumList = WiFi.scanNetworks();
  // print the network number and name for each network found:
  for (int currentSsid = 0; currentSsid < ssidNumList; currentSsid++)
  {
    if (WiFi.SSID(currentSsid) == ssid)
    {
      WiFi.begin(ssid, password);
      break;
    }
    else if (WiFi.SSID(currentSsid) == ssid1)
    {
      WiFi.begin(ssid1, password1);
      break;
    }
    else if (WiFi.SSID(currentSsid) == ssid2)
    {
      WiFi.begin(ssid2, password2);
      break;
    }
    else
      break;
  }
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
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

    for (JsonPair keyValue : jsonObject.as<JsonObject>())
    {
      JsonObject ledObject = keyValue.value().as<JsonObject>();
      int id = ledObject["id"];
      bool isOpen = ledObject["isOpen"];
      if (isOpen)
      {
        ledStates[id] = HIGH;
        digitalWrite(ledPins[id], ledStates[id]);
      }
      else
      {
        ledStates[id] = LOW;
      }
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