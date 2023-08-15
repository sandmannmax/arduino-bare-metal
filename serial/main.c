#include "uart_hal.h"
#include <avr/interrupt.h>

int main(void) {
  uart_init(9600, 0);
  sei();

  uint8_t d;

  while (1) {
    if (uart_read_count() > 0) {
      d = uart_read_byte();
      uart_send_byte(d);
      uart_send_byte('-');
    }
  }

  return 0;
}
