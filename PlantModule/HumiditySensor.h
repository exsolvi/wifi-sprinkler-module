#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H
#include "Thread.h"
#include "Sensor.h"

class HumiditySensor: public Thread , virtual public Sensor
{
  public:
    explicit HumiditySensor(int sensorPin) : sensorPin(sensorPin) {};
    void run();
    void sense();
    double getSensorValue();
    double getSensorValueMax();
    double getSensorValueMin();
    const char* getName();
  private:
    int sensorPin;
    double humidity = 0;
    double max_humidity = 0;
    double min_humidity = 1025;
    int count = 0;
};

#endif /* HUMIDITYSENSOR_H */

