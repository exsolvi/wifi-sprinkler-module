#include <Arduino.h>
#include "HumiditySensor.h"
#include "Sensor.h"
#include "Logger.h"
#include <string>

const char* NAME = "humidity";

void HumiditySensor::run() {
  sense();
  //Logger::log("In HumiditySensor.run()");
  runned();
}

const char* HumiditySensor::getName() {
  return NAME;
}

double HumiditySensor::getSensorValue() {
  double value = humidity;
  humidity = 0;
  count = 0;
  return value;
}

double HumiditySensor::getSensorValueMax() {
  double val = max_humidity;
  max_humidity = 0;
  return val;
}

double HumiditySensor::getSensorValueMin() {
  double val = min_humidity;
  min_humidity = 1025;
  return val;
}

void HumiditySensor::sense() {
  double sensorValue = analogRead(A0);
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
    Logger::log(logMsg);
  */
}

