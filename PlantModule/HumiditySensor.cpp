#include <Arduino.h>
#include "ThreadController.h"
#include "HumiditySensor.h"
#include "Sensor.h"
#include "Logger.h"
#include <string>

const int SAMPLES = 10;
const char* NAME = "humidity";
int min, max;

void HumiditySensor::run() {
  sense();
  runned();
}

const char* HumiditySensor::getName() {
  return NAME;
}

double HumiditySensor::getSensorValue() {
  double val = humidity;
  humidity = 0;
  count = 0;
  return val;
}

double HumiditySensor::getSensorValueMax() {
  double val = max_humidity;
  max_humidity = 0;
  return val;
}

double HumiditySensor::getSensorValueMin() {
  double val = min;
  min = 1025;
  return val;
}

void HumiditySensor::sense() {
  int sensorValue = analogRead(A0);
  count++;
  double avg = humidity - humidity / count + sensorValue / count;
  humidity = avg;
  if (sensorValue > max_humidity) {
    max_humidity = sensorValue;
  }
  if (sensorValue < min_humidity) {
    min_humidity = sensorValue;
  }
  /*
    String key = String("Humidity: ");
    String val = String(humidity);
    String logMsg = key + val;
    Logger::log(std::string(logMsg.c_str()));
  */
}

