#include <ArduinoJson.h>
#include "DataSender.h"
#include "Logger.h"
#include <Arduino.h>
#include <vector>
#include <ESP8266HTTPClient.h>

void DataSender::addSensor(Sensor * sensor) {
  sensors.push_back(sensor);
}

String DataSender::encodeSensorData() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["sensorname"] = "Tomat";

  for (Sensor * s : sensors) {
    float sensorValue = s->getAndResetCurrentValue();
    //long val = round(sensor);
    //String strValue = String(sensorValue);
    //String strValue = String("\"") + String(sensorValue) + String("\"");
    //root[s->getName()] = strValue.c_str();
    root[s->getName()] = sensorValue;
    //Logger::log(s->getName());
    //Logger::log(strValue.c_str());
    //Logger::log(String(val));
  }

  String str;
  root.prettyPrintTo(str);
  Logger::log(str.c_str());
  Serial.println(str.c_str());
  return str;
}

void DataSender::send(String payload) {
  String returnvalue = "-1";
  HTTPClient http;
  http.begin(destinationUrl, fingerprint);
  Logger::log(destinationUrl);
  http.addHeader("Content-Type", "application/json");
  Logger::log("Posting");
  int httpCode =  http.POST(payload);
  if (httpCode != 200) {
    Logger::log("Not successful");
  } else {
    returnvalue = http.getString();
    Logger::log(String("Successful: ") + returnvalue);
  }
  Logger::log("Ending");
  http.end();

}
void DataSender::run() {
  String payload = encodeSensorData();
  send(payload);
  //Logger::log("In DataSender::run()");
  runned();
}

void DataSender::setDestinationUrl(char const* url) {
  Logger::log("Set destinationUrl: ");
  Logger::log(url);
  destinationUrl = url;
}

void DataSender::setFingerprint(char const* fp) {
  fingerprint = fp;
}

