#include "../serial/uart_hal.h"
#include "adc_hal.h"
#include <util/delay.h>

void send_packet_prefix() {
  uart_send_byte(0xf0);
  uart_send_byte(0x0f);
  uart_send_byte(0xf0);
  uart_send_byte(0x0f);
}

int main(void) {
  uart_init(9600, 0);
  adc_init();
  sei();

  _delay_ms(1);

  while (1) {
    uint16_t a = adc_read();

    send_packet_prefix();
    uart_send_byte(a & 0xff);
    uart_send_byte((a & 0xff00) >> 8);

    _delay_ms(250);
  }

  return 0;
}
