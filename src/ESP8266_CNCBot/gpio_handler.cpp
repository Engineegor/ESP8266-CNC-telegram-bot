#include <Arduino.h>
#include <ESP8266WiFi.h>

#define BUTTON_PIN 14

#define GPIO_TASK_PRECOUNTER 30

int gpio_task_counter 	= 0;

bool button_flag		= false;
bool button_flag_inv	= false;


void button_click(int button_pin, bool* rise_trig, bool* fall_trig) {
			bool button_state = !digitalRead(BUTTON_PIN);
	static	bool button_trig = false;
	if ( button_state && !button_trig) {button_trig = 1; *rise_trig = true;}
	if (!button_state &&  button_trig) {button_trig = 0; *fall_trig = true;}
}

void GPIO_SETUP() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void GPIO_TASK() {
	if (gpio_task_counter >= GPIO_TASK_PRECOUNTER) {
		gpio_task_counter = 0;

		button_click(BUTTON_PIN, &button_flag, &button_flag_inv);

	} else {
		gpio_task_counter++;
	}
}