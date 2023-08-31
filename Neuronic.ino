#include <BLEDevice.h>
#include <BLEAdvertising.h> // 引入BLEAdvertising库
#include "setup.h"
#include "loop.h"

#define UUID 1836475137

void setup() {
  Serial.begin(115200);
  
  wifisetup();
  
  BLEDevice::init("E32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLEUUID((uint16_t)UUID));
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                       BLEUUID((uint16_t)(UUID + 1)),
                                       BLECharacteristic::PROPERTY_READ |
                                       BLECharacteristic::PROPERTY_WRITE
                                       );
  pService->start();
  
  // 添加以下代码来设置广播数据
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinInterval(0x06); // 设置广播最小间隔
  pAdvertising->setMaxInterval(0x08); // 设置广播最大间隔
  
  pAdvertising->start();
  
  pServer->startAdvertising();

  Serial.println("Started advertising");
}

void loop() {
  wifi();
  delay(1000);
}