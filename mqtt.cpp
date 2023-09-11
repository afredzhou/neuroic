
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "setup.h"
#include "loop.h"

#define QOS         2
#define PIN 26
#define clean_session false
extern bool connected;
int f =0;
uint8_t count;
unsigned long period;
unsigned long previousMillis = 0;

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);
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
  // blinkled(count);
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
    wifi();
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
  connectAWS();

}
void aws()
{ int message=f;
  countperiod(message);
  client.loop();
}
