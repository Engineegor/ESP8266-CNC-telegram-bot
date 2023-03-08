#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

#include "net_param.h"
#include "wifi_handler.h"
#include "web_handler.h"

#define CONNECT_TIMEOUT 15000

bool client_or_AP = 0;
int net_num = 0;

IPAddress local_ip(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

WiFiClientSecure client;
ESP8266WebServer server(80);
MDNSResponder mdns;

int scan_for_familiar_net() {
	net_num = WiFi.scanNetworks();

	String familiar_ssid = wifi_ssid_chr;

	Serial.println(F("Awailable networks:"));
	for (int i = 0; i < net_num; ++i) {Serial.println(WiFi.SSID(i));}
	Serial.println();

	for (int i = 0; i < net_num; ++i)
	{
		if(WiFi.SSID(i) == familiar_ssid) return i;
	}
	return -1;
}

void setup_web() {
	

	if (MDNS.begin("esp8266", WiFi.localIP())) {
    	Serial.println(F("MDNS responder started"));
  	}

	Serial.println(F("Setting up web server"));

	web_init();
	

	MDNS.addService("http", "tcp", 80);

	Serial.println(F("Server successfully begin"));
}

void set_soft_AP() {
	Serial.println(F("Setting up AP"));

	client_or_AP = 1;

	WiFi.softAPConfig(local_ip, gateway, subnet);
	WiFi.softAP(F("ESP_move_bot"));
	WiFi.softAPIP();
	delay(100);
	setup_web();
}

bool try_to_connect(int val) {

	Serial.print(F("Trying to connect to: "));
	Serial.println(wifi_ssid_chr);

	WiFi.begin(wifi_ssid_chr, wifi_pass_chr);
	int connect_millis = millis();

	while ((WiFi.status() != WL_CONNECTED) && ((millis() - connect_millis) <= CONNECT_TIMEOUT)) {
		Serial.print(F("."));
		delay(100);
	}
	Serial.println();

	if (WiFi.status() == WL_CONNECTED) {
		Serial.println(F("Successfully"));
		Serial.print(F("IP "));
		Serial.println(WiFi.localIP().toString());
		Serial.println();

		setup_web();

		return true;
	} else {
		Serial.println(F("Failed"));
		Serial.println();
		return false;
	}
}

void WIFI_SETUP() {

	Serial.println(F("WiFi SETUP\n"));

	param_init();
	read_net_param();

	if (wifi_ssid_chr[0] == 0xFF || wifi_pass_chr[0] == 0x0) {
		Serial.println(F("There is no saved net parameters\n"));
		set_soft_AP();
	} else {
		int net_val = scan_for_familiar_net();

		if (net_val == -1) {
			set_soft_AP();
		} else {
			if (try_to_connect(net_val)) {Serial.println(F("Web started"));
			} else {set_soft_AP();}
		}
	}

	client.setInsecure();

	Serial.println(F("Setup done"));
}

void WIFI_TASK() {
	server.handleClient();
}
