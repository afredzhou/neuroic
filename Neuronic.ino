#include <BLEDevice.h>
#include "setup.h"
#include "loop.h"
#define UUID  1836475137

void setup() {
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
  pServer->getAdvertising()->start();
}

void loop() {
  wifi();
  delay(1000);
}