#include "led.h"
#include <util/delay.h>

int main(void) {
  ledInit();

  while (1) {
    ledToggle();
    _delay_ms(500);
  }

  return 0;
}
