class HumiditySensor: public Thread
{
public:
  void run();
  HumiditySensor(int sensorPin);
private:
  int sensorPin;
};

