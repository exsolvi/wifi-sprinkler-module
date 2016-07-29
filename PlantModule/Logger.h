#ifndef LOGGER_H
#define LOGGER_H
#include "Arduino.h"
#include <string>

class Logger {
  private:
  public:
    void static log(std::string msg);
    void static log(char const* msg);
    void static log(String msg);
};

#endif /* LOGGER_H */

