#include "Sensor.h"
#include <limits>

const char* Sensor::getName() {
  return NAME;
}

float Sensor::getCurrentValue() {
  return averageValue;
}

float Sensor::getAndResetCurrentValue() {
  float value = averageValue;
  averageValue = 0;
  count = 0;
  return value;
}

float Sensor::getMaxValue() {
  return maxValue;
}

float Sensor::getAndResetMaxValue() {
  float value = maxValue;
  maxValue = 0;
  return value;
}

float Sensor::getMinValue() {
  return minValue;
}

float Sensor::getAndResetMinValue() {
  float value = minValue;
  minValue = std::numeric_limits<float>::max();
  return value;
}

void Sensor::updateSensorValue(float value) {
  count++;
  float avg = averageValue - averageValue / count + value / count;
  averageValue = avg;
  if (value > maxValue) {
    maxValue = value;
  }
  if (value < minValue) {
    minValue = value;
  }
}

