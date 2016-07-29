#ifndef CONFIG_H
#define CONFIG_H
#include <ArduinoJson.h>

using namespace ArduinoJson;

class Config {
  private:
    String baseUrl;
    const char* fingerprint;
    String fetchedJson;
    String fetchFromHttpsUrl(String url);
  public:
    Config(String baseUrl, char const* fingerprint);
    JsonObject& getConfig();
};
#endif /* CONFIG_H */

