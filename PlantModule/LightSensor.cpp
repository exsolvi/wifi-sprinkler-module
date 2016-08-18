#include "LightSensor.h"

LightSensor::LightSensor() {
  NAME = "light";
  lightMeter = new BH1750();
  lightMeter->begin();
}

LightSensor::~LightSensor() {
  delete lightMeter;
}

void LightSensor::run() {
  sense();
  //Logger::log("In LightSensor.run()");
  runned();
}

void LightSensor::sense() {
  float light = lightMeter->readLightLevel();
  if (isnan(light)) {
    return;
  }
  updateSensorValue(light);
}

