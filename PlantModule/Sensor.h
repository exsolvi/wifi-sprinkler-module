#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
  public:
    virtual void sense() = 0;
    virtual double getSensorValue() = 0;
    virtual double getSensorValueMax() = 0;
    virtual double getSensorValueMin() = 0;
    virtual const char* getName() = 0;
};

#endif /* SENSOR_H */

