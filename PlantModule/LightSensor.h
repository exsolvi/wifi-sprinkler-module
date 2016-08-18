#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include "Thread.h"
#include "Sensor.h"
#include <BH1750.h>

class LightSensor: public Thread , virtual public Sensor
{
  private:
    BH1750 * lightMeter;
  public:
    LightSensor();
    ~LightSensor();
    void run();
    void sense();

};

#endif /* LIGHTSENSOR_H */

