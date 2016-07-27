#include <ArduinoJson.h>
#include "DataSender.h"
#include "Logger.h"
#include <Arduino.h>
#include <vector>

void DataSender::addSensor(Sensor * sensor) {
  /*
    Sensor[sensorSize + 1] newSensors;
    for (int i = 0; i < sensorSize; i++) {
      newSensors[i] = sensors[i];
    }
    newSensors[i + 1] = sensor;
    sensorSize++;
    Logger::log("Added new sensor");
  */
  sensors.push_back(sensor);
}

String DataSender::encodeSensorData() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["sensorname"] = "gurka";
  root["moisture"] = "-1";
  //root["humidity"] = "-1";
  root["temperature"] = "-1";
  root["light"] = "-1";

  for (Sensor * s : sensors) {
    root[s->getName()] = s->getSensorValue();
    //Logger::log(String(s->getSensorValue()).c_str());
  }
  String str;
  root.prettyPrintTo(str);
  Logger::log(str.c_str());
  return str;
}

void DataSender::send(String payload) {
  HTTPClient http;
  http.setReuse(true);
  http.begin(destinationUrl, fingerprint);
  http.addHeader("Content-Type", "application/json");
  Logger::log("Starting to send request");
  Logger::log("Posting");
  http.POST(payload);
  Logger::log("Writing to stream");
  http.writeToStream(&Serial);
  Logger::log("Ending");
  http.end();

}
void DataSender::run() {
  String payload = encodeSensorData();
  send(payload);
  runned();
}

