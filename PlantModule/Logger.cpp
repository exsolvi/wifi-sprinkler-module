#include "Logger.h"

void Logger::log(std::string msg) {
  Logger::log(msg.c_str());
}

void Logger::log(String msg) {
  Logger::log(msg.c_str());
}

#define LOG_UDP

#ifdef LOG_UDP
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string>

void Logger::log(char const* msg) {
  const int UDP_PACKET_SIZE = strlen(msg);
  char udpBuffer[UDP_PACKET_SIZE + 1];
  strcpy(udpBuffer, msg);
  strcat(udpBuffer, "\n");
  String ip = WiFi.localIP().toString();
  String strPort = String("23") + ip.substring(ip.lastIndexOf(".")+1);
  unsigned int remotePort = strPort.toInt();
  unsigned int udplocalPort = 2390;
  IPAddress ipBroadCast(192, 168, 1, 0);
  WiFiUDP udp;
  udp.begin(udplocalPort);
  udp.beginPacket(ipBroadCast, remotePort);
  udp.write(udpBuffer, sizeof(udpBuffer));
  udp.endPacket();
}
#endif

#ifdef LOG_SERIAL
void Logger::log(char const* msg) {
  Serial.println(msg);
}
#endif

