#include <WiFi.h>
#include <WiFiManager.h>
WiFiServer server(80);
void handleReq(WiFiClient c) {
  c.println("HTTP/1.1 200 OK");
  c.println("Content-Type: text/plain");
  c.println();
  c.println("Connected!");
}
void wifisetup() {
  WiFiManager wifiManager;
  // 尝试连接保存的WiFi网络，如果没有保存的网络，则启动一键配网界面，并设置热点名称
  bool connected = wifiManager.autoConnect("myESP32");
  if (connected) {
    Serial.println("Connected to WiFi");
    server.begin();
  } else {
    Serial.println("Failed to connect to WiFi and timeout occurred");
    // 连接失败时的逻辑
  }
}
void wifi() {
  WiFiClient c = server.available();
  if (c) {
    handleReq(c);
    c.stop();
  }
}