#include "imports.h"
SoftwareSerial BTSerial(D2, D3,false);
//RGBStts rgbSt=RgbStts(LED);
Sensors sensors;
void setup(){
    sensors.start();
Serial.begin(115200);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  BTSerial.begin(9600);
  
}
void loop(){
if (BTSerial.available()) {
    char c=BTSerial.read();
    Serial.println(c);
    if(c=='0')
      digitalWrite(LEDR, HIGH);
    else 
    digitalWrite(LEDR, LOW);
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read());}
   //BTSerial.write("{\"humidity\":67,\"temperature\":23}");
    sendData(sensors, BTSerial);

}
/*
#include <SoftwareSerial.h>

void setup() {
  
}
void loop() {
  
}

*/