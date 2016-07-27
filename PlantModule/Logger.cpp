#include "Logger.h"

void Logger::log(std::string msg) {
  Logger::log(msg.c_str());
}

#define LOG_UDP

#ifdef LOG_UDP
#ifndef WIFIUDP_H
#include <WiFiUdp.h>
#endif
#include <string>

void Logger::log(char const* msg) {
  const int UDP_PACKET_SIZE = strlen(msg);
  char udpBuffer[UDP_PACKET_SIZE+1];
  strcpy(udpBuffer, msg);
  strcat(udpBuffer, "\n");

  unsigned int udpRemotePort = 2391;
  unsigned int udplocalPort = 2390;
  IPAddress ipBroadCast(192, 168, 1, 0);
  WiFiUDP udp;
  udp.begin(udplocalPort);
  udp.beginPacket(ipBroadCast, udpRemotePort);
  udp.write(udpBuffer, sizeof(udpBuffer));
  udp.endPacket();
}
#endif

#ifdef LOG_SERIAL
#include <Arduino.h>

void Logger::log(char const* msg) {
  Serial.println(msg);
}
#endif

