#include <BH1750FVI.h>
#include <Wire.h>

#include <Ticker.h>
#include <Thread.h>
#include <ThreadController.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include "Utils.h"
#include "OTASupport.h"
#include "HumiditySensor.h"

//const char* host = "i75aeqr8f2.execute-api.eu-west-1.amazonaws.com";
//const int httpsPort = 443;
const char* fingerprint = "64 39 f5 dd a5 f6 64 d2 aa 2f 9d 3c dc 6e 42 90 a9 e6 b6 55";
bool safeMode = true;

BH1750FVI LightSensor;
int lux;

String fetchFromHttpsUrl(String url, char const* fingerprint) {
  HTTPClient http;
  http.setReuse(true);
  http.begin(url, fingerprint);

  String result;
  int httpCode = http.GET();
  if (httpCode > 0) {
    //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      result = http.getString();
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return result;

}

JsonObject& parseConfig(String jsonConfig) {
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& config = jsonBuffer.parseObject(jsonConfig);

  // Test if parsing succeeds.
  if (!config.success()) {
    Serial.println("parseObject() failed");
  }
  return config;
}

HumiditySensor sensor (0);
ThreadController runner;
Ticker timer;

void runnerCallback() {
  runner.run();
}
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting");

  setupWiFi();
  setupOTA();
  setClockFromNTP();

  clearScreen();
  printSystemInfo();
  String bootstrapConfig = fetchFromHttpsUrl("https://i75aeqr8f2.execute-api.eu-west-1.amazonaws.com/production/bootstrap", fingerprint);
  JsonObject& config = parseConfig(bootstrapConfig);

  const char* configurl = config["configUrl"];

  char deviceConfigUrl[255];
  sprintf(deviceConfigUrl, "%s/%u", configurl, ESP.getChipId());
  Serial.println(deviceConfigUrl);

  String deviceConfigJson = fetchFromHttpsUrl(deviceConfigUrl, fingerprint);
  JsonObject& deviceConfig = parseConfig(deviceConfigJson);
  const char* deviceId = deviceConfig["deviceId"];
  const char* deviceName = deviceConfig["deviceName"];
  const char* dataPath = deviceConfig["dataPath"];
  const char* updateFrequence = deviceConfig["updateFrequence"];

  Serial.println(deviceId);
  Serial.println(deviceName);
  Serial.println(dataPath);
  Serial.println(updateFrequence);
  
  if (ESP.getResetReason() == "Power on" || ESP.getResetReason() == "Software/System restart" || ESP.getResetReason() == "External System") {
    Serial.println("Good reset mode - fully operational");
    safeMode = false;
  } else {
    Serial.println("Bad reset mode - going into safe mode");
  }

  LightSensor.begin();
  LightSensor.setMode(Continuously_High_Resolution_Mode); 

  sensor.setInterval(10);
  runner.add(&sensor);
  //timer.attach_ms(250, runnerCallback);
}

void loop() {
  ArduinoOTA.handle();
  if (!safeMode) {
    runner.run();
      lux = LightSensor.getAmbientLight();
  Serial.print("Ambient light intensity: ");
  Serial.print(lux);
  Serial.println(" lux");
  delay(2000);
  }
  delay(10);
}


