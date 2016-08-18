#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H
#include "Thread.h"
#include "Sensor.h"

class MoistureSensor: public Thread , virtual public Sensor
{
  private:
    int sensorPin;
  public:
    explicit MoistureSensor(int sensorPin);
    void run();
    void sense();
};

#endif /* MOISTURESENSOR_H */

