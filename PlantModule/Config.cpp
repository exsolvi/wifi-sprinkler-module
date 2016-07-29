#include "Config.h"
#include <ESP8266HTTPClient.h>

Config::Config(String baseUrl, char const* fingerprint): baseUrl(baseUrl), fingerprint(fingerprint) {
  fetchedJson = fetchFromHttpsUrl(baseUrl);
};

String Config::fetchFromHttpsUrl(String url) {
  HTTPClient http;
  http.setReuse(true);
  http.begin(url, fingerprint);

  String result;
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      result = http.getString();
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return result;
}

JsonObject& Config::getConfig() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& config = jsonBuffer.parseObject(fetchedJson);

  // Test if parsing succeeds.
  if (!config.success()) {
    Serial.println("parseObject() failed");
  }
  return config;
};
