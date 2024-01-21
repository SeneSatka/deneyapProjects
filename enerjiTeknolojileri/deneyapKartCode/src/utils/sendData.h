unsigned long prevMillis = millis();
const unsigned long delayInterval = 100;

void sendDataWithWiFi(Sensors sensors, WSCC &wsc)
{
    if (millis() - prevMillis >= delayInterval)
    {
        StaticJsonDocument<200> doc;
        doc["device"] = 0;
        doc["humidity"] = sensors.getHumidity();
        doc["temperature"] = sensors.getTemperature();
        doc["smokeValue"] = sensors.getSmokeValue();
        doc["PIR"] = sensors.getPirValue() == HIGH ? 1 : 0;
        doc["ledsState"]["1"] = sensors.led1State;
        doc["ledsState"]["2"] = sensors.led2State;
        doc["ledsState"]["3"] = sensors.led3State;
        doc["ledsState"]["4"] = sensors.led4State;
        doc["doorState"] = sensors.doorState;
        doc["windowState"] = sensors.windowState;
        String output;
        serializeJson(doc, output);
        Serial.println(output);
        wsc.send(output);
        prevMillis = millis();
    }
}
void sendDataWithBluetooth() {}