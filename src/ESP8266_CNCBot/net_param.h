#include <Arduino.h>

#define ADDR_START 	0
#define SSID_LEN	32
#define PASS_LEN	32
#define ID_LEN 		16
#define	TOKEN_LEN	64
#define PARAM_LEN	4

extern char wifi_ssid_chr[SSID_LEN];
extern char wifi_pass_chr[PASS_LEN];
extern char wifi_id_chr[ID_LEN];
extern char wifi_token_chr[TOKEN_LEN];
extern uint8_t	acc_sens_val;
extern uint8_t	gyr_sens_val;
extern uint8_t	bot_pref;

extern void param_init();
extern void save_net_param();
extern void read_net_param();
extern void save_bot_param();
extern void read_bot_param();
extern void save_param();
extern void read_param();
void EEPROM_writeStr(char *text, int text_addr, int text_len);
void EEPROM_readStr(char *text, int text_addr, int text_len);