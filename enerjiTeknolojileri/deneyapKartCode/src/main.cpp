#include "utils/imports.h"

const char *ssid = "FiberHGW_ZTAT49_2.4GHz";
const char *password = "33khNYhCUeDf";
const char *websockets_connection_string = "ws://192.168.1.111:8080"; // Enter server adress

float humidity = 0, temperature = 0;

RGBStts RgbStatus = RGBStts(LEDR, LEDG, LEDB);
Sensors sensors;
IRrecv irrecv(RECV_PIN);
decode_results results;
WebsocketsClient _wsc;
int servoPos = 90;
WSCC wsc(_wsc);
void onMessageCallback(WebsocketsMessage message);
Servo servo;
void setup()
{
  DefinePinMode();
  Serial.begin(115200);
  connectWifi(ssid, password, RgbStatus);
  wsc.start(websockets_connection_string, onMessageCallback);
  irrecv.enableIRIn();
  sensors.start();
  servo.attach(D9);
}
void loop()
{

  servo.write(servoPos);
  digitalWrite(LED_PIN_1, sensors.led1State);
  digitalWrite(LED_PIN_2, sensors.led2State);
  digitalWrite(LED_PIN_3, sensors.led3State);
  digitalWrite(LED_PIN_4, sensors.led4State);
  int ldr1 = map(analogRead(A1), 0, 8191, 0, 100);
  int ldr2 = map(analogRead(A2), 0, 8191, 0, 100);

  if (ldr1 - ldr2 > 10)
  {
    if (servoPos != 0)
      servoPos -= 10;
  }
  else if (ldr2 - ldr1 > 10)
  {
    if (servoPos != 180)
      servoPos += 10;
  }

  if (irrecv.decode(&results))
  {
    // if (results.value == IR_NUM_1)
    //   Serial.println("1");
    // if (results.value == IR_NUM_2)
    //   Serial.println("2");
    // if (results.value == IR_NUM_3)
    //   Serial.println("3");
    // if (results.value == IR_NUM_4)
    //   Serial.println("4");
    // if (results.value == IR_NUM_5)
    //   Serial.println("5");
    // if (results.value == IR_NUM_6)
    //   Serial.println("6");
    // if (results.value == IR_NUM_7)
    //   Serial.println("7");
    // if (results.value == IR_NUM_8)
    //   Serial.println("8");
    // if (results.value == IR_NUM_9)
    //   Serial.println("9");
    // if (results.value == IR_NUM_0)
    //   Serial.println("0");
    // if (results.value == IR_SQUARE)
    //   Serial.println("#");
    // if (results.value == IR_STAR)
    //   Serial.println("*");
    // if (results.value == IR_UP)
    //   Serial.println("UP");
    // if (results.value == IR_DOWN)
    //   Serial.println("DOWN");
    // if (results.value == IR_RIGHT)
    //   Serial.println("RIGHT");
    // if (results.value == IR_LEFT)
    //   Serial.println("LEFT");
    // if (results.value == IR_OK)
    //   sendDataWithWiFi(sensors, wsc);
    irrecv.resume();
  }
  sendDataWithWiFi(sensors, wsc);
  delay(100);
  wsc.wsc.poll();
}
void onMessageCallback(WebsocketsMessage message)
{
  Serial.println(message.data());
  StaticJsonDocument<200> doc;
  deserializeJson(doc, message.data());
  int code = doc["code"];
  int aa = doc["ledsState"][1];
  // Serial.println(aa);
  sensors.led1State = doc["ledsState"]["1"] == 1 ? HIGH : LOW;
  sensors.led2State = doc["ledsState"]["2"] == 1 ? HIGH : LOW;
  sensors.led3State = doc["ledsState"]["3"] == 1 ? HIGH : LOW;
  sensors.led4State = doc["ledsState"]["4"] == 1 ? HIGH : LOW;
}