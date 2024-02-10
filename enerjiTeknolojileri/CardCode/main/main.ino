#define dhtType DHT11
#define dhtPin D11
#define PIR D12
#define LED_PIN_1 D4
#define LED_PIN_2 D5
#define LED_PIN_3 D6
#define LED_PIN_4 D7
#define BUZZER_PIN D8
#define DOOR_SERVO D9
#define WINDOW_SERVO D10
#define MQ2 A0

#include <Arduino.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "DHT.h"

DHT dht(dhtPin, dhtType);
class Sensors {
public:
  int led1State = LOW, led2State = LOW, led3State = LOW, led4State = LOW, doorState = LOW, windowState = LOW;

  Sensors(){};
  void start() {
    dht.begin();
  };

  float getHumidity() {
    return dht.readHumidity();
  };

  float getTemperature() {
    return dht.readTemperature();
  };

  int getPirValue() {
    return digitalRead(PIR);
  };

  int getSmokeValue() {
    return analogRead(MQ2);
  };
};

class RGBStts {
public:
  int ledR_pin;
  int ledG_pin;
  int ledB_pin;

  RGBStts(int _ledR_pin, int _ledG_pin, int _ledB_pin) {
    ledR_pin = _ledR_pin;
    ledG_pin = _ledG_pin;
    ledB_pin = _ledB_pin;
  };

  void closeAll() {
    digitalWrite(ledR_pin, LOW);
    digitalWrite(ledG_pin, LOW);
    digitalWrite(ledB_pin, LOW);
  };

  void red() {
    closeAll();
    digitalWrite(ledR_pin, HIGH);
  };

  void green() {
    closeAll();
    digitalWrite(ledG_pin, HIGH);
  };

  void blue() {
    closeAll();
    digitalWrite(ledB_pin, HIGH);
  };

  void success() {
    green();
  };

  void error() {
    red();
  };

  void signal(int delayMS = 500) {
    blue();
  };
};

SoftwareSerial Bluetooth(D2, D3, false);
RGBStts rgbStts = RGBStts(LEDR, LEDG, LEDB);
Sensors sensors;
Servo doorServo;
Servo windowServo;
StaticJsonDocument<200> recaiveDoc;
StaticJsonDocument<200> sendDoc;

bool recaive = false;
String data = "";

unsigned long prevMillis = millis();
const unsigned long delayInterval = 1000;
void setup() {
  Serial.begin(115200);
  Bluetooth.begin(9600);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(MQ2, INPUT);

  sensors.start();

  doorServo.attach(DOOR_SERVO);
  doorServo.write(0);

  windowServo.attach(WINDOW_SERVO);
  windowServo.write(0);
}


void loop() {
  digitalWrite(LED_PIN_1, sensors.led1State);
  digitalWrite(LED_PIN_2, sensors.led2State);
  digitalWrite(LED_PIN_3, sensors.led3State);
  digitalWrite(LED_PIN_4, sensors.led4State);
  if (sensors.getPirValue() == HIGH){ 
     digitalWrite(BUZZER_PIN, HIGH);
     delay(100);
        digitalWrite(BUZZER_PIN, LOW);
         delay(100);
     }
  if(sensors.getSmokeValue()>7000){ 
    sensors.windowState=HIGH;
     digitalWrite(BUZZER_PIN, HIGH);
     delay(100);
        digitalWrite(BUZZER_PIN, LOW);
         delay(100);
     }

  if (sensors.doorState == HIGH) doorServo.write(90);
  else doorServo.write(0);

  if (sensors.windowState == HIGH) windowServo.write(90);
  else windowServo.write(0);

  if (Bluetooth.available()) {
    char c = Bluetooth.read();
    if (c == '{') {
      recaive = true;
      rgbStts.signal();
      data += "{";
    } else if (c == '}') {
      recaive = false;
      data += "}";
      Serial.println(data);

      deserializeJson(recaiveDoc, data);

      sensors.led1State = recaiveDoc["1"] == 1 ? HIGH : LOW;
      sensors.led2State = recaiveDoc["2"] == 1 ? HIGH : LOW;
      sensors.led3State = recaiveDoc["3"] == 1 ? HIGH : LOW;
      sensors.led4State = recaiveDoc["4"] == 1 ? HIGH : LOW;

      sensors.doorState = recaiveDoc["d"] == 1 ? HIGH : LOW;
      sensors.windowState = recaiveDoc["w"] == 1 ? HIGH : LOW;
      data = "";
      rgbStts.success();
    } else {
      if (recaive) data += c;
    }
  }

  if (Serial.available()) Bluetooth.write(Serial.read());

  if (millis() - prevMillis >= delayInterval) {

    sendDoc["humidity"] = sensors.getHumidity();

    sendDoc["temperature"] = (int)sensors.getTemperature();

    sendDoc["smokeValue"] = sensors.getSmokeValue();

    sendDoc["PIR"] = (sensors.getPirValue() == HIGH ? 1 : 0);

    sendDoc["led1State"] = sensors.led1State;
    sendDoc["led2State"] = sensors.led2State;
    sendDoc["led3State"] = sensors.led3State;
    sendDoc["led4State"] = sensors.led4State;

    sendDoc["doorState"] = sensors.doorState;
    sendDoc["windowState"] = sensors.windowState;

    String output;
    serializeJson(sendDoc, output);
    const char *cstr = output.c_str();
    Bluetooth.write(cstr);

    prevMillis = millis();
  }
}
