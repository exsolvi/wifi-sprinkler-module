#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() {
  NAME = "temperature";
  bmp = new Adafruit_BMP085();
  bmp->begin();
}

TemperatureSensor::~TemperatureSensor() {
  delete bmp;
}

void TemperatureSensor::run() {
  sense();
  runned();
}
void TemperatureSensor::sense() {
  float temperature = bmp->readTemperature();
  if (isnan(temperature)) {
    return;
  }
  updateSensorValue(temperature);
}

