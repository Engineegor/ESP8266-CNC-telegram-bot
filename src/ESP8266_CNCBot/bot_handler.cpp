#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#include "wifi_handler.h"
#include "bot_param.h"
#include "net_param.h"
#include "gpio_handler.h"

#define LISTEN_PERIOD	10000

UniversalTelegramBot bot(CHARLIE_TOKEN, client);

unsigned int 	listen_counter	= 0;
bool			alarm_enable	= 0;
bool			alarm_e_enable		= 0;
int 			val_destination	= 0;

void ping_handler() {
	bot.sendMessage(wifi_id_chr, F("I am alive"));
}

void ip_handler() {
	bot.sendMessage(wifi_id_chr, WiFi.localIP().toString());
}

void send_alm_handler() {
	String msg = F("Signal at program start ");
	msg += alarm_enable ? F("enabled") : F("disabled");
	msg += F("\n Signal at program end ");
	msg += alarm_e_enable ? F("enabled") : F("disabled");
	bot.sendMessage(wifi_id_chr, msg);
}

void alm_handler(bool state) {
	alarm_enable = state;

	bitWrite(bot_pref, 0, alarm_enable);

	send_alm_handler();
	save_param();
}

void alm_e_handler(bool state_inv) {
	alarm_e_enable = state_inv;

	bitWrite(bot_pref, 1, alarm_e_enable);

	send_alm_handler();
	save_param();
}

void handle_messages(int msgnum) {
	for (int i = 0; i < msgnum; i++)
	{
		String chat_id 	= bot.messages[i].chat_id;
		String text 	= bot.messages[i].text;
		String username = bot.messages[i].from_name;

		Serial.print(F("Telegram| "));
		Serial.print(username);
		Serial.print(F(": "));
		Serial.println(text);

		if (chat_id == wifi_id_chr) {
			if 		(text == "/ping")					{ping_handler();}
			else if (text == "/ip") 					{ip_handler();}
			else if (text == "/alarm")					{send_alm_handler();}
			else if (text == "/alarm_on")				{alm_handler(1);}
			else if (text == "/alarm_off")				{alm_handler(0);}
			else if (text == "/alarm_end_on")			{alm_e_handler(1);}
			else if (text == "/alarm_end_off")			{alm_e_handler(0);}
		}
	}
}

void bot_listen(){
	int got = bot.getUpdates(bot.last_message_received + 1);

	if (got) {handle_messages(got);}
}

void bot_say_alarm(bool inv) {
	String msg = "Alarm! \nProgram ";
	msg += inv ? F("ended!") : F("started!");
	bot.sendMessage(wifi_id_chr, msg);
}

void bot_talk() {
	if (button_flag && alarm_enable) {
		button_flag = false;
		bot_say_alarm(0);
	}
	if (button_flag_inv && alarm_e_enable) {
		button_flag_inv = false;
		bot_say_alarm(1);
	}
}

void BOT_SETUP() {
	if (WiFi.status() == WL_CONNECTED) {

		read_param();

		alarm_enable 	= bitRead(bot_pref, 0);
		alarm_e_enable	= bitRead(bot_pref, 1);

		read_bot_param();

		bot.updateToken(wifi_token_chr);
		Serial.println(F("Sending message to telegram bot\n"));

		String powerup_msg = F("ESP CNC detector is Online\nConnected to: ");
			powerup_msg	+= WiFi.SSID();
			powerup_msg += F("\nIP: ");
			powerup_msg += WiFi.localIP().toString();
			powerup_msg += F("\nSignal at program start ");
			powerup_msg += alarm_enable ? F("enabled") : F("disabled");
			powerup_msg += F("\nSignal at program end ");
			powerup_msg += alarm_e_enable ? F("enabled") : F("disabled");

		bot.sendMessage(wifi_id_chr, powerup_msg);
	}
}

void BOT_TASK() {
	if (WiFi.status() == WL_CONNECTED) {
		if (listen_counter > LISTEN_PERIOD) {
			listen_counter = 0;
			bot_listen();
		} else {
			listen_counter++;
		}

		bot_talk();

	}
}