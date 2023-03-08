#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>

extern WiFiClientSecure client;
extern ESP8266WebServer server;

extern void WIFI_SETUP();
extern void WIFI_TASK();