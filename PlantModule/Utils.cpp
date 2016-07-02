#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

const char* ssid = "SMURFHEM";
const char* password = "ExsolviRocksAtStorgatan";

void printSystemInfo() {
  Serial.println("----- System details -----------------------------------------");
  Serial.print("Vcc                   : ");
  Serial.println(ESP.getVcc());
  Serial.print("FreeHeap              : ");
  Serial.println(ESP.getFreeHeap());
  Serial.print("ChipId                : ");
  Serial.println(ESP.getChipId());
  Serial.print("BootVersion           : ");
  Serial.println(ESP.getBootVersion());
  Serial.print("BootMode              : ");
  Serial.println(ESP.getBootMode());
  Serial.print("CpuFreqMHz            : ");
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print("FlashChipId           : ");
  Serial.println(ESP.getFlashChipId());
  Serial.print("FlashChipSize         : ");
  Serial.println(ESP.getFlashChipSize());
  Serial.print("FlashChipRealSize     : ");
  Serial.println(ESP.getFlashChipRealSize());
  Serial.print("FlashChipSizeByChipId : ");
  Serial.println(ESP.getFlashChipSizeByChipId());
  Serial.print("SdkVersion            : ");
  Serial.println(ESP.getSdkVersion());
  Serial.print("FlashChipSpeed        : ");
  Serial.println(ESP.getFlashChipSpeed());
  Serial.print("FlashChipMode         : ");
  Serial.println(ESP.getFlashChipMode());
  Serial.print("SketchSize            : ");
  Serial.println(ESP.getSketchSize());
  Serial.print("FreeSketchSpace       : ");
  Serial.println(ESP.getFreeSketchSpace());
  Serial.print("ResetReason           : ");
  Serial.println(ESP.getResetReason());
  Serial.println("----- IP details ---------------------------------------------");
  Serial.print("IP Address            : ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet                : ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway               : ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("----- Time details -------------------------------------------");
  Serial.print("Time                  : ");
  time_t now = time(nullptr);
  Serial.println(ctime(&now));
  Serial.println("+++++ System ready +++++++++++++++++++++++++++++++++++++++++++");
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

