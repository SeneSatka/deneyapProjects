#ifndef IMPORTS_H

#define IMPORTS_H
#define dhtType DHT11
#define dhtPin D11
#define PIR D12
#define LED_PIN_1 D4
#define LED_PIN_2 D5
#define LED_PIN_3 D6
#define LED_PIN_4 D7
#define BUZZER_PIN D8

#define MQ2 A0
#define LDR1 A1
#define LDR2 A2

#define IR_NUM_1 16753245
#define IR_NUM_2 16736925
#define IR_NUM_3 16769565
#define IR_NUM_4 16720605
#define IR_NUM_5 16712445
#define IR_NUM_6 16761405
#define IR_NUM_7 16769055
#define IR_NUM_8 16754775
#define IR_NUM_9 16748655
#define IR_NUM_0 16750695
#define IR_SQUARE 16756815
#define IR_STAR 16738455
#define IR_UP 16718055
#define IR_DOWN 16730805
#define IR_RIGHT 16734885
#define IR_LEFT 16716015
#define IR_OK 16726215

#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <SoftwareSerial.h>

#include "DHT.h"
#include "definePinMode.h"
#include "ws.h"
#include "sensors.h"
#include "sendData.h"
#include "RGBStatus.h"
#include "WiFiConnection.h"

#endif
