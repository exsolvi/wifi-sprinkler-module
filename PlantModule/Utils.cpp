#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

const char* ssid = "SMURFHEM";
const char* password = "ExsolviRocksAtStorgatan";

void printSystemInfo() {
  Serial.println(F("----- System details -----------------------------------------"));
  Serial.print(F("Vcc                   : "));
  Serial.println(ESP.getVcc());
  Serial.print(F("FreeHeap              : "));
  Serial.println(ESP.getFreeHeap());
  Serial.print(F("ChipId                : "));
  Serial.println(ESP.getChipId());
  Serial.print(F("BootVersion           : "));
  Serial.println(ESP.getBootVersion());
  Serial.print(F("BootMode              : "));
  Serial.println(ESP.getBootMode());
  Serial.print(F("CpuFreqMHz            : "));
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print(F("FlashChipId           : "));
  Serial.println(ESP.getFlashChipId());
  Serial.print(F("FlashChipSize         : "));
  Serial.println(ESP.getFlashChipSize());
  Serial.print(F("FlashChipRealSize     : "));
  Serial.println(ESP.getFlashChipRealSize());
  Serial.print(F("FlashChipSizeByChipId : "));
  Serial.println(ESP.getFlashChipSizeByChipId());
  Serial.print(F("SdkVersion            : "));
  Serial.println(ESP.getSdkVersion());
  Serial.print(F("FlashChipSpeed        : "));
  Serial.println(ESP.getFlashChipSpeed());
  Serial.print(F("FlashChipMode         : "));
  Serial.println(ESP.getFlashChipMode());
  Serial.print(F("SketchSize            : "));
  Serial.println(ESP.getSketchSize());
  Serial.print(F("FreeSketchSpace       : "));
  Serial.println(ESP.getFreeSketchSpace());
  Serial.print(F("ResetReason           : "));
  Serial.println(ESP.getResetReason());
  Serial.print(F("ResetInfo             : "));
  Serial.println(ESP.getResetInfo());
  Serial.println(F("----- IP details ---------------------------------------------"));
  Serial.print(F("IP Address            : "));
  Serial.println(WiFi.localIP());
  Serial.print(F("Subnet                : "));
  Serial.println(WiFi.subnetMask());
  Serial.print(F("Gateway               : "));
  Serial.println(WiFi.gatewayIP());
  Serial.println(F("----- Time details -------------------------------------------"));
  Serial.print(F("Time                  : "));
  time_t now = time(nullptr);
  Serial.print(ctime(&now));
  Serial.println(F("+++++ System ready +++++++++++++++++++++++++++++++++++++++++++"));
}

void setupWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}

void setClockFromNTP() {
  configTime(2 * 3600, 0, "gbg1.ntp.se", "gbg1.ntp.se");
  while (!time(nullptr)) {
    delay(10);
  }
}

void clearScreen() {
  for (int i = 0; i < 100; i++) {
    Serial.println("");
  }
}


