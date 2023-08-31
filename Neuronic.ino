#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEAdvertising.h>

#define UUID 1836475137

void setup() {
  Serial.begin(115200);

  // 初始化WiFi和其他设置
  wifisetup();

  // 初始化BLE设备
  BLEDevice::init("E32");

  // 创建BLE服务器
  BLEServer *pServer = BLEDevice::createServer();
  
  // 创建BLE服务
  BLEService *pService = pServer->createService(BLEUUID((uint16_t)UUID));

  // 创建BLE特征
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                       BLEUUID((uint16_t)(UUID + 1)),
                                       BLECharacteristic::PROPERTY_READ |
                                       BLECharacteristic::PROPERTY_WRITE
                                       );
  
  // 启动BLE服务
  pService->start();

  // 启动BLE广播
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->setScanResponse(true);
  pAdvertising->start();

  Serial.println("Started advertising");
}

void loop() {
  // 处理其他任务
  wifi();
  delay(1000);
}