#include <Wire.h>
#include <Ticker.h>
#include <Thread.h>
#include <ThreadController.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoOTA.h>
#include "Utils.h"
#include "OTASupport.h"
#include "HumiditySensor.h"
#include "Config.h"
#include "Logger.h"
#include "DataSender.h"

const char* fingerprint = "64 39 f5 dd a5 f6 64 d2 aa 2f 9d 3c dc 6e 42 90 a9 e6 b6 55";
bool safeMode = true;

ThreadController runner;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting");
  setupWiFi();
  setupOTA();
  setClockFromNTP();
//  pinMode(A0, INPUT);

  clearScreen();
  printSystemInfo();
  /*
    Config bootstrapConfig("https://i75aeqr8f2.execute-api.eu-west-1.amazonaws.com/production/bootstrap", fingerprint);
    JsonObject& bootstrapConfigModel = bootstrapConfig.getConfig();
    char deviceConfigUrl[255];
    sprintf(deviceConfigUrl, "%s/%u", (const char*)bootstrapConfigModel["configUrl"], ESP.getChipId());
    Serial.println(deviceConfigUrl);

    Config deviceConfig(deviceConfigUrl, fingerprint);
    JsonObject& deviceConfigModel = deviceConfig.getConfig();

    const char* deviceId = deviceConfigModel["deviceId"];
    const char* deviceName = deviceConfigModel["deviceName"];
    const char* dataPath = deviceConfigModel["dataPath"];
    const char* updateFrequence = deviceConfigModel["updateFrequence"];

    Serial.println(deviceId);
    Serial.println(deviceName);
    Serial.println(dataPath);
    Serial.println(updateFrequence);
  */
  if (ESP.getResetReason() == "Power on" || ESP.getResetReason() == "Software/System restart" || ESP.getResetReason() == "External System") {
    Serial.println("Good reset mode - fully operational");
    Logger::log("Good reset mode - fully operational");
    safeMode = false;
  } else {
    Serial.println("Bad reset mode - going into safe mode");
    Logger::log(ESP.getResetReason().c_str());
    Logger::log("Bad reset mode - going into safe mode");
  }

  if (!safeMode) {
    Logger::log("1");
    HumiditySensor humiditySensor (A0);
    Logger::log("2");
    humiditySensor.setInterval(100);
    Logger::log("3");
    const char* dataPath = "http://example.com";
    Logger::log("4");
    DataSender dataSender (dataPath, fingerprint);
    Logger::log("5");

    dataSender.setInterval(5000);
    Logger::log("6");
    dataSender.addSensor(&humiditySensor);
    Logger::log("7");
    runner.add(&dataSender);
    Logger::log("8");
    runner.add(&humiditySensor);
    Logger::log("9");
  }
}

void loop() {
  ArduinoOTA.handle();
  if (!safeMode) {
    runner.run();
  }
  delay(10);
}



