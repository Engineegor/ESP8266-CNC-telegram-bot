#include <Arduino.h>
#include "wifi_handler.h"
#include "bot_handler.h"
#include "OS.h"
#include "gpio_handler.h"

long int task_counter = 0;

void OS_KERNEL_SETUP() {
	Serial.begin(115200);
	WIFI_SETUP();
	BOT_SETUP();
	GPIO_SETUP();
}

void OS_KERNEL_TASK() {
	if (TASK_DELAY >= millis() - task_counter) {
		task_counter = millis();
	} else {
		WIFI_TASK();
		GPIO_TASK();
		BOT_TASK();
	}//*/
}