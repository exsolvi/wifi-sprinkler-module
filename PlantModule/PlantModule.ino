#include <Wire.h>
#include <ThreadController.h>
#include <ArduinoOTA.h>
#include "Utils.h"
#include "OTASupport.h"
#include "MoistureSensor.h"
#include "HumiditySensor.h"
#include "PressureSensor.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include "Config.h"
#include "Logger.h"
#include "DataSender.h"

const char* fingerprint = "64 39 f5 dd a5 f6 64 d2 aa 2f 9d 3c dc 6e 42 90 a9 e6 b6 55";
bool safeMode = true;

ThreadController runner;
MoistureSensor moistureSensor (A0);
HumiditySensor humiditySensor (D5);
PressureSensor pressureSensor;
LightSensor lightSensor;
TemperatureSensor temperatureSensor;
DataSender dataSender;
Thread rebootThread = Thread();

int count = 0;

void reboot() {
  Logger::log("RebootThread is rebooting node");
  Serial.println("RebootThread is rebooting node");
  ESP.restart();
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
    Serial.println("1");
    moistureSensor.setInterval(1000);
    humiditySensor.setInterval(1000);
    pressureSensor.setInterval(1000);
    lightSensor.setInterval(1000);
    temperatureSensor.setInterval(1000);
    Logger::log("2");
    Serial.println("2");
    dataSender.setDestinationUrl("https://i75aeqr8f2.execute-api.eu-west-1.amazonaws.com/production/metric");
    Logger::log("4");
    Serial.println("4");
    dataSender.setFingerprint(fingerprint);
    Logger::log("5");
    Serial.println("5");
    dataSender.setInterval(10000);
    Logger::log("6");
    Serial.println("6");
    dataSender.addSensor(&moistureSensor);
    dataSender.addSensor(&humiditySensor);
    dataSender.addSensor(&pressureSensor);
    dataSender.addSensor(&lightSensor);
    dataSender.addSensor(&temperatureSensor);
    Logger::log("7");
    Serial.println("7");
    runner.add(&dataSender);
    Logger::log("8");
    Serial.println("8");
    runner.add(&moistureSensor);
    runner.add(&humiditySensor);
    runner.add(&pressureSensor);
    runner.add(&lightSensor);
    runner.add(&temperatureSensor);
    Logger::log("9");
    Serial.println("9");
    rebootThread.setInterval(300000);
    rebootThread.onRun(reboot);
    runner.add(&rebootThread);
    delay(1000);
  }
}

void loop() {
  ArduinoOTA.handle();
  if (!safeMode) {
    //count++;
    //Logger::log(String(count).c_str());
    runner.run();
  }
}


