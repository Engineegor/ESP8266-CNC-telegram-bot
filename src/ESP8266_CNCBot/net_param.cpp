#include <EEPROM.h>
#include "net_param.h"

char wifi_ssid_chr[SSID_LEN];
char wifi_pass_chr[PASS_LEN];
char wifi_id_chr[ID_LEN];
char wifi_token_chr[TOKEN_LEN];
uint8_t	acc_sens_val;
uint8_t	gyr_sens_val;
uint8_t	bot_pref;
char param_chr[PARAM_LEN];

void param_init() {
	EEPROM.begin(ADDR_START + SSID_LEN + PASS_LEN + ID_LEN + TOKEN_LEN + PARAM_LEN);
}

void save_net_param() {
	Serial.println(F("\nSave net param to EEPROM"));
	EEPROM_writeStr(wifi_ssid_chr, ADDR_START,  SSID_LEN);
	EEPROM_writeStr(wifi_pass_chr, ADDR_START + SSID_LEN,	PASS_LEN);
	EEPROM.commit();
	Serial.println(wifi_ssid_chr);
	Serial.println(wifi_pass_chr);
	Serial.println();
}

void read_net_param() {
	Serial.println(F("\nReading net param from EEPROM"));
	EEPROM_readStr(wifi_ssid_chr, ADDR_START,  SSID_LEN);
	EEPROM_readStr(wifi_pass_chr, ADDR_START + SSID_LEN,	PASS_LEN);
	Serial.println(wifi_ssid_chr);
	Serial.println(wifi_pass_chr);
	Serial.println();
}

void save_bot_param() {
	Serial.println(F("\nSave bot param to EEPROM"));
	EEPROM_writeStr(wifi_id_chr,	ADDR_START + SSID_LEN + PASS_LEN,  ID_LEN);
	EEPROM_writeStr(wifi_token_chr, ADDR_START + SSID_LEN + PASS_LEN + ID_LEN,	TOKEN_LEN);
	EEPROM.commit();
	Serial.println(wifi_id_chr);
	Serial.println(wifi_token_chr);
	Serial.println();
}

void read_bot_param() {
	Serial.println(F("\nReading bot param from EEPROM"));
	EEPROM_readStr(wifi_id_chr, 	ADDR_START + SSID_LEN + PASS_LEN,  ID_LEN);
	EEPROM_readStr(wifi_token_chr,	ADDR_START + SSID_LEN + PASS_LEN + ID_LEN,	TOKEN_LEN);
	Serial.println(wifi_id_chr);
	Serial.println(wifi_token_chr);
	Serial.println();
}

void save_param() {
	Serial.println(F("\nSave preferences to EEPROM"));
	param_chr[0] = bot_pref;
	param_chr[2] = acc_sens_val;
	param_chr[3] = gyr_sens_val;
	EEPROM_writeStr(param_chr,		ADDR_START + SSID_LEN + PASS_LEN + ID_LEN + TOKEN_LEN, PARAM_LEN);
	EEPROM.commit();
	Serial.println(param_chr);
	Serial.println();
}

void read_param() {
	Serial.println(F("\nRead preferences to EEPROM"));
	EEPROM_readStr(param_chr,		ADDR_START + SSID_LEN + PASS_LEN + ID_LEN + TOKEN_LEN, PARAM_LEN);
	bot_pref 		= param_chr[0];
	acc_sens_val 	= param_chr[2];
	gyr_sens_val	= param_chr[3];
	Serial.print(bot_pref, BIN);
	Serial.print(" ");
	Serial.print(acc_sens_val);
	Serial.print(" ");
	Serial.println(gyr_sens_val);
}


void EEPROM_writeStr(char *text, int text_addr, int text_len) {
	for (int i = 0; i < text_len; ++i) {
		EEPROM.write(text_addr + i, text[i]);
		delay(12);
	}
}

void EEPROM_readStr(char *text, int text_addr, int text_len) {
	for (int i = 0; i < text_len; ++i) {
		text[i] = EEPROM.read(text_addr + i);
		delay(7);
	}
}