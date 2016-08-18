#include "PressureSensor.h"

PressureSensor::PressureSensor() {
  NAME = "pressure";
  bmp = new Adafruit_BMP085();
  bmp->begin();
}

PressureSensor::~PressureSensor() {
  delete bmp;
}

void PressureSensor::run() {
  sense();
  //Logger::log("In PressureSensor.run()");
  runned();
}

void PressureSensor::sense() {
  float pressure = bmp->readPressure();
  if (isnan(pressure)) {
    return;
  }
  updateSensorValue(pressure);
}

