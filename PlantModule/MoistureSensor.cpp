#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int pin) {
  NAME = "moisture";
  sensorPin = pin;
}

void MoistureSensor::run() {
  sense();
  runned();
}


void MoistureSensor::sense() {
  float moisture = analogRead(sensorPin);
  updateSensorValue(moisture);
}

