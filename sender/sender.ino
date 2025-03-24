#include "BLEDevice.h"

const int k1 = 15;
const int k2 = 4;
const int k3 = 5;
const int k4 = 18;
const int k5 = 19;
const int k6 = 21;
const int k7 = 22;
const int k8 = 23;
const int k9 = 34;
const int k10 = 35;
String x="";
bool st = false;
/* Specify the Service UUID of Server */
static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
/* Specify the Characteristic UUID of Server */
static BLEUUID    charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                            uint8_t* pData, size_t length, bool isNotify)
{
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.println((char*)pData);
}

class MyClientCallback : public BLEClientCallbacks
{
  void onConnect(BLEClient* pclient)
  {
    
  }

  void onDisconnect(BLEClient* pclient)
  {
    connected = false;
    Serial.println("onDisconnect");
  }
};

/* Start connection to the BLE Server */
bool connectToServer()
{
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());
    
  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

    /* Connect to the remote BLE Server */
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

    /* Obtain a reference to the service we are after in the remote BLE server */
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr)
  {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");


  /* Obtain a reference to the characteristic in the service of the remote BLE server */
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr)
  {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic");

  /* Read the value of the characteristic */
  /* Initial value is 'Hello, World!' */
  if(pRemoteCharacteristic->canRead())
  {
    std::string value = pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }

  if(pRemoteCharacteristic->canNotify())
  {
    pRemoteCharacteristic->registerForNotify(notifyCallback);

  }

    connected = true;
    return true;
}
/* Scan for BLE servers and find the first one that advertises the service we are looking for. */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
 /* Called for each advertising BLE server. */
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    /* We have found a device, let us now see if it contains the service we are looking for. */
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID))
    {
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    }
  }
};


void setup()
{
  pinMode(k1,INPUT);
  pinMode(k2,INPUT);
  pinMode(k3,INPUT);
  pinMode(k4,INPUT);
  pinMode(k5,INPUT);
  pinMode(k6,INPUT);
  pinMode(k7,INPUT);
  pinMode(k8,INPUT);
  pinMode(k9,INPUT);
  pinMode(k10,INPUT);
  attachInterrupt(digitalPinToInterrupt(k1),LED1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k2),LED2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k3),LED3,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k4),LED4,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k5),LED5,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k6),LED6,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k7),LED7,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k8),LED8,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k9),LED9,CHANGE);
  attachInterrupt(digitalPinToInterrupt(k10),LED10,CHANGE); 
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("ESP32-BLE-Client");

  /* Retrieve a Scanner and set the callback we want to use to be informed when we
     have detected a new device.  Specify that we want active scanning and start the
     scan to run for 5 seconds. */
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}


void loop()
{

  /* If the flag "doConnect" is true, then we have scanned for and found the desired
     BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
     connected we set the connected flag to be true. */
  if (doConnect == true)
  {
    if (connectToServer())
    {
      Serial.println("We are now connected to the BLE Server.");
    } 
    else
    {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  /* If we are connected to a peer BLE Server, update the characteristic each time we are reached
     with the current time since boot */
  if (connected)
  {
    String newValue = x;
    if (st==true){
    Serial.println("Setting new characteristic value to \"" + newValue + "\"");
    
    /* Set the characteristic's value to be the array of bytes that is actually a string */
    pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
    st = false;
    /* You can see this value updated in the Server's Characteristic */
    }
  }
  else if(doScan)
  {
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }
  
  delay(20); /* Delay a second between loops */
}


void LED1() {
  bool state = digitalRead(k1);
  switch (state){
    case 1:
      x = "0";
      break;
    case 0:
      x = "1";
      break;
    
    
    }
  
  
  st = true;
}

void LED2() {
  bool state2 = digitalRead(k2);
  switch (state2){
    case 1:
      x = "2";
      break;
    case 0:
      x = "3";
      break;
    
    
    }
  st = true;
}

void LED3() {
  bool state3 = digitalRead(k3);
  switch (state3){
    case 1:
      x = "4";
      break;
    case 0:
      x = "5";
      break;
    
    
    }
  st = true;
}

void LED4() {
  bool state4 = digitalRead(k4);
  switch (state4){
    case 1:
      x = "6";
      break;
    case 0:
      x = "7";
      break;
    
    
    }
  st = true;
}

void LED5() {
  bool state5 = digitalRead(k5);
  switch (state5){
    case 1:
      x = "8";
      break;
    case 0:
      x = "9";
      break;
    
    
    }
  st = true;
}

void LED6() {
  bool state6 = digitalRead(k6);
  switch (state6){
    case 1:
      x = "10";
      break;
    case 0:
      x = "11";
      break;
    
    
    }
  st = true;
}

void LED7() {
  bool state7 = digitalRead(k7);
  switch (state7){
    case 1:
      x = "12";
      break;
    case 0:
      x = "13";
      break;
    
    
    }
  st = true;
}

void LED8() {
  bool state8 = digitalRead(k8);
  switch (state8){
    case 1:
      x = "14";
      break;
    case 0:
      x = "15";
      break;
    
    
    }
  st = true;

}

void LED9() {
  bool state9 = digitalRead(k9);
  switch (state9){
    case 1:
      x = "16";
      break;
    case 0:
      x = "17";
      break;
    
    
    }
  st = true;

}

void LED10() {
  bool state10 = digitalRead(k10);
  switch (state10){
    case 1:
      x = "18";
      break;
    case 0:
      x = "19";
      break;
    
    
    }
  st = true;

}
