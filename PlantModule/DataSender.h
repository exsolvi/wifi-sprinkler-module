#ifndef DATASENDER_H
#define DATASENDER_H
#include <vector>
#include "Thread.h"
#include "Sensor.h"

class DataSender: public Thread
{
  public:
    void setDestinationUrl(char const* url);
    void setFingerprint(char const* fp);
    void addSensor(Sensor * sensor);
    void run();
  private:
    std::vector<Sensor*> sensors;
    char const* destinationUrl;
    char const* fingerprint;
    int sensorSize = 1;
    String encodeSensorData();
    void send(String payload);
};

#endif /* DATASENDER_H */

