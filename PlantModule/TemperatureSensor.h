#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H
#include "Thread.h"
#include "Sensor.h"
#include <Adafruit_BMP085.h>

class TemperatureSensor: public Thread , virtual public Sensor
{
  private:
    Adafruit_BMP085 * bmp;
  public:
    TemperatureSensor();
    ~TemperatureSensor();
    void run();
    void sense();
};

#endif /* TEMPERATURESENSOR_H */

