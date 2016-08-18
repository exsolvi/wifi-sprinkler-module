#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H
#include "Thread.h"
#include "Sensor.h"
#include "DHT.h"

class HumiditySensor: public Thread , public Sensor
{
  private:
    DHT* dht;
  public:
    explicit HumiditySensor(int pin);
    ~HumiditySensor();
    void run();
    void sense();
};

#endif /* HUMIDITYSENSOR_H */

