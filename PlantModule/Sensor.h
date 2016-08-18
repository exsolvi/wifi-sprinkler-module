#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
  private:
    int count;
    float averageValue;
    float maxValue;
    float minValue;
  protected:
    const char* NAME = "--NAME--";
    void updateSensorValue(float value);
  public:
    virtual void sense() = 0;
    float getCurrentValue();
    float getAndResetCurrentValue();
    float getMaxValue();
    float getAndResetMaxValue();
    float getMinValue();
    float getAndResetMinValue();
    const char* getName();
};

#endif /* SENSOR_H */

