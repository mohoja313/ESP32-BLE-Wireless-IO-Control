#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

const int R1 = 22;
const int R2 = 25;
const int R3 = 19;
const int R4 = 21;
const int R5 = 32;
const int R6 = 33;
const int R7 = 4;
const int R8 = 26;
const int R9 = 18;
const int R10 = 15;
const int Ground = 5;
int i = 0;
String TEXT = "";
/* BLEServer *pServer = BLEDevice::createServer();
BLEService *pService = pServer->createService(SERVICE_UUID);
BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       ); */

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;


void setup()
{
  Serial.begin(115200);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);
  pinMode(R10, OUTPUT);
  pinMode(Ground, OUTPUT);
  digitalWrite(Ground,LOW);
  Serial.println("Starting BLE Server!");

  BLEDevice::init("ESP32-BLE-Server");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  
  /* BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );*/

  pCharacteristic->setValue("Hello, World!");
  pService->start();
  //BLEAdvertising *pAdvertising = pServer->getAdvertising();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  //pAdvertising->start();
  Serial.println("Characteristic defined! Now you can read it in the Client!");
}

void loop()
{
  std::string value = pCharacteristic->getValue();
  Serial.print("The new characteristic value is: ");
  TEXT = value.c_str();
  Serial.println(TEXT.c_str());
  i = atoi(TEXT.c_str());
  switch (i){
  
        case 0:
          digitalWrite(R1, LOW);
          break;
        case 1:
          digitalWrite(R1, HIGH);
          break;

        case 2:
          digitalWrite(R2, LOW);
          break;
        case 3:
          digitalWrite(R2, HIGH);
          break;
        
        case 4:
          digitalWrite(R3, LOW);
          break;
        case 5:
          digitalWrite(R3, HIGH);
          break;

        case 6:
          digitalWrite(R4, LOW);
          break;
        case 7:
          digitalWrite(R4, HIGH);
          break;

        case 8:
          digitalWrite(R5, LOW);
          break;
        case 9:
          digitalWrite(R5, HIGH);
          break;

        case 10:
          digitalWrite(R6, LOW);
          break;
        case 11:
          digitalWrite(R6, HIGH);
          break;

        case 12:
          digitalWrite(R7, LOW);
          break;
        case 13:
          digitalWrite(R7, HIGH);
          break;

        case 14:
          digitalWrite(R8, LOW);
          break;
        case 15:
          digitalWrite(R8, HIGH);
          break;

        case 16:
          digitalWrite(R9, LOW);
          break;
        case 17:
          digitalWrite(R9, HIGH);
          break;

        case 18:
          digitalWrite(R10, LOW);
          break;
        case 19:
          digitalWrite(R10, HIGH);
          break;          
        
        
        }
}
