#include "../analog/adc_hal.h"
#include "../serial/uart_hal.h"
#include <util/delay.h>

#define PACKET_LENGTH 32

static volatile uint8_t buffer[PACKET_LENGTH];
static volatile uint8_t buffer_pos = 0;

void send_packet_prefix() {
  uart_send_byte(0xf0);
  uart_send_byte(0x0f);
  uart_send_byte(0xf0);
  uart_send_byte(0x0f);
}

void send_packet() {
  send_packet_prefix();

  for (uint8_t i = 0; i < PACKET_LENGTH; ++i) {
    uart_send_byte(buffer[i]);
    buffer[i] = 0;
  }

  buffer_pos = 0;
}

int main(void) {
  uart_init(9600, 0);
  adc_init();
  sei();

  _delay_ms(1);

  while (1) {
    uint16_t a = adc_read();

    buffer[buffer_pos++] = (a & 0xff00) >> 8;
    buffer[buffer_pos++] = a & 0xff;

    if (buffer_pos >= PACKET_LENGTH)
      send_packet();
  }

  return 0;
}
