/*
  Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "setup.h"
#include <Adafruit_NeoPixel.h>
#define QOS         2
#define PIN 26
#define clean_session false
#define MAX_LED 16
#define ADD true

#define SUB false
int f =0;
uint8_t count;
unsigned long period;
unsigned long previousMillis = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAX_LED, PIN, NEO_RGB + NEO_KHZ800);

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);
// led blink
void blinkled(uint8_t a)
{
  uint8_t i = 0;
  uint32_t color = strip.Color(255, 0, 0);

  for (i = 0; i < 16; i++)
  {

    if (i == a)
      strip.setPixelColor(i, color);

    else
      strip.setPixelColor(i, 0);

    strip.show();
    delay(20);
  }
}
// interval (间隔)
void countperiod(int message)
{
  unsigned long currentMillis = millis();
  period = 2001 - 200 * message;
  if (currentMillis - previousMillis >= period)
  {

    count = count + 1;
    previousMillis = currentMillis;
  };
  if (count >= 17)
  {
    count = 0;
  };
  blinkled(count);
}
// 亚马逊信息回调
void messageHandler(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  if (payload.isEmpty())
  {
    f = 0;
  }
  else
  {
    f = doc["message"];
  }
  Serial.println(f);
  int iotmessage(f);
}

void connectAWS()
{
   delay(100);
  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
    wifisetup();
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(10);
  }

  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}
int iotmessage(int f) {f=f+0 ;return f;};
void awssetup()
{
  Serial.begin(9600);
  connectAWS();
  strip.begin();
  strip.show();
}
void aws()
{ int message=f;
  countperiod(message);
  client.loop();
}
