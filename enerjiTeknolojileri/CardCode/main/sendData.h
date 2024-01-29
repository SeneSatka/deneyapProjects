unsigned long prevMillis = millis();
const unsigned long delayInterval = 100;
void sendData(Sensors sensors,SoftwareSerial &bluetooth/*,WSCC &wsc*/){
  if (millis() - prevMillis >= delayInterval)
    {
       StaticJsonDocument<200> doc;
        doc["device"] = 0;
        doc["humidity"] = sensors.getHumidity();
        doc["temperature"] =(int) sensors.getTemperature();
        doc["smokeValue"] = sensors.getSmokeValue();
        doc["PIR"] = (sensors.getPirValue() == HIGH ? 1 : 0);
      
        doc["led1State"] = sensors.led1State;
        doc["led2State"] = sensors.led2State;
        doc["led3State"] = sensors.led3State;
        doc["led4State"] = sensors.led4State;
        doc["doorState"] = sensors.doorState;
        doc["windowState"] = sensors.windowState;
        String output;
        serializeJson(doc, output);
        //wsc.send(output);
        const char *cstr = output.c_str();
       bluetooth.write(cstr);
        prevMillis = millis();
    }
}
