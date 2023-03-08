#include "wifi_handler.h"
#include "html_css.h"
#include "net_param.h"

extern int net_num;

void handler_NotFound() {
	server.send(404, "text/plain", "Not found");
}


void handle_WiFiList() {

	Serial.println("Web page: WiFi list");

	net_num = WiFi.scanNetworks();

	server.send(200, "text/html", WiFiList_page(net_num));
	Serial.println();
}

void handle_WiFiList() {

	ESP.restart();
}

void handle_NetParam() {
	Serial.println("Web page: saved parameters");
	Serial.println();

	String ssid = server.arg("ssid");
	String pass = server.arg("pass");

	if (ssid == "") {
		read_net_param();
		ssid = wifi_ssid_chr;
		pass = wifi_pass_chr;
	}
	server.send(200, "text/html", NetParam_page(ssid, pass, 0));
}

void handle_SaveParam() {
	Serial.println("Web page: save parameters to EEPROM");
	Serial.println();

	String ssid = server.arg("ssid");
	String pass = server.arg("pass");
	if (ssid != "") {
		ssid.toCharArray(wifi_ssid_chr, SSID_LEN);
		pass.toCharArray(wifi_pass_chr, PASS_LEN);
		save_net_param();
	}
	server.send(200, "text/html", NetParam_page(ssid, pass, 1));
}

void handle_BotParam() {
	Serial.println("Web page: saved bot parameters");
	Serial.println();

	String ssid = server.arg("ssid");
	String pass = server.arg("pass");

	if (ssid == "") {
		read_bot_param();
		ssid = wifi_id_chr;
		pass = wifi_token_chr;
	}
	server.send(200, "text/html", BotParam_page(ssid, pass, 0));
}

void handle_newBotParam() {
	Serial.println("Web page: save bot parameters to EEPROM");
	Serial.println();

	String id = server.arg("ssid");
	String token = server.arg("pass");
	if (id != "") {
		id.toCharArray(wifi_id_chr, ID_LEN);
		token.toCharArray(wifi_token_chr, TOKEN_LEN);
		save_bot_param();
	}
	server.send(200, "text/html", BotParam_page(id, token, 1));
}


void web_init() {
	server.on("/", handle_WiFiList);
	server.on("/reboot", handle_Reboot);
	server.on("/savedParam", handle_NetParam);
	server.on("/saveParam", handle_SaveParam);
	server.on("/botParam", handle_BotParam);
	server.on("/newBotParam", handle_newBotParam);
	server.onNotFound(handler_NotFound);

	server.begin();
}