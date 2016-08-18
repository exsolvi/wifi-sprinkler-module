#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(int sensorPin) {
  NAME = "humidity";
  dht = new DHT(sensorPin, DHT11);
  dht->begin();
}

HumiditySensor::~HumiditySensor() {
  delete dht;
}

void HumiditySensor::run() {
  sense();
  //Logger::log("In HumiditySensor.run()");
  runned();
}

void HumiditySensor::sense() {
  float humidity = dht->readHumidity();
  if (isnan(humidity)) {
    return;
  }
  updateSensorValue(humidity);
}

