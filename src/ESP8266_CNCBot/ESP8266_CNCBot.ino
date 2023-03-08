#include "OS.h"

void setup() {
  OS_KERNEL_SETUP();
}

void loop() {
  OS_KERNEL_TASK();
}