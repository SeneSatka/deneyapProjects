#include "esp32-hal-gpio.h"
#include "DHT.h"
DHT dht(dhtPin, dhtType);
class Sensors
{
public:
    int led1State = LOW, led2State = LOW, led3State = LOW, led4State = LOW, doorState = LOW, windowState = LOW;
    Sensors(){};
    void start()
    {
        dht.begin();
    }
    float getHumidity()
    {
        return dht.readHumidity();
    }
    float getTemperature()
    {
        return dht.readTemperature();
    }
    int getPirValue()
    {
        return digitalRead(PIR);
    }
    int getSmokeValue()
    {
        return analogRead(MQ2);
    }
};