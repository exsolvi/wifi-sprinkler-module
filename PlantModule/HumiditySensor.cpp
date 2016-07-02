#include <Arduino.h>
#include "Thread.h"
#include "ThreadController.h"
#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(int sensorPin) : sensorPin(sensorPin) {}

const int maxSamples = 100;

int sensorValue = 0;
int samples = 0;
int reading = 0;

void HumiditySensor::run() {
  reading += analogRead(sensorPin);
  samples++;
  if (samples > maxSamples) {
    sensorValue = reading / samples;
    Serial.println(sensorValue);
    samples = 0;
    reading = 0;
  }
  runned();
}


