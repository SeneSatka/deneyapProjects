
void connectWifi(const char *ssid, const char *password, RGBStts &RgbStatus)
{
    RgbStatus.red();
    WiFi.begin(ssid, password);
    while (!WiFi.isConnected())
    {
        Serial.print(".");
        delay(100);
    }
    Serial.print("\nConnected, IP: ");
    Serial.println(WiFi.localIP());
    RgbStatus.success();
}