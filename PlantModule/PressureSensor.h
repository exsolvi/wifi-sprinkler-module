#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H
#include "Thread.h"
#include "Sensor.h"
#include <Adafruit_BMP085.h>

class PressureSensor: public Thread , virtual public Sensor
{
  private:
    Adafruit_BMP085 * bmp;
  public:
    PressureSensor();
    ~PressureSensor();
    void run();
    void sense();

};

#endif /* PRESSURESENSOR_H */

