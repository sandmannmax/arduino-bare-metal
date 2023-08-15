#include "../serial/uart_hal.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void start_signal() {
  DDRD |= (1 << DDD2);
  PORTD &= ~(1 << PORTD2);
  _delay_ms(20);
  PORTD |= (1 << PORTD2);
}

void wait_for_high_pulse(uint32_t max_us) {
  uint32_t max_cycles = max_us * (F_CPU / 1000000);
  uint32_t cycles = 0;
  while ((PIND & (1 << PIND2)) == 0 &&
         cycles < max_cycles) // wait for high pulse
    ++cycles;
}

void wait_for_low_pulse(uint32_t max_us) {
  uint32_t max_cycles = max_us * (F_CPU / 1000000);
  uint32_t cycles = 0;
  while (PIND & (1 << PIND2) && cycles < max_cycles) // wait for low pulse
    ++cycles;
}

void response_signal() {
  DDRD &= ~(1 << DDD2);
  wait_for_low_pulse(50);
  wait_for_high_pulse(100);
  wait_for_low_pulse(100);
}

uint8_t read_byte() {
  uint8_t d = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    wait_for_high_pulse(60);
    _delay_us(50);
    if (PIND & (1 << PIND2))
      d = (d << 1) | 0x01;
    else
      d = d << 1;
    wait_for_low_pulse(80);
  }

  return d;
}

uint8_t get_hex_ascii(uint8_t d) {
  if (d < 10)
    return '0' + d;
  else
    return 'A' + d - 10;
}

void uart_send_string(char *s) {
  while (*s != 0) {
    uart_send_byte(*s);
    ++s;
  }
}

void uart_send_byte_as_hex(uint8_t d) {
  uint8_t h = (d & 0xf0) >> 4;
  uint8_t l = d & 0x04;

  uart_send_byte(get_hex_ascii(h));
  uart_send_byte(get_hex_ascii(l));
}

void uart_send_byte_as_dec(uint8_t d) {
  uint8_t d2 = (d % 1000) / 100;
  uint8_t d1 = (d % 100) / 10;
  uint8_t d0 = d % 10;

  if (d2 > 0)
    uart_send_byte(get_hex_ascii(d2));
  uart_send_byte(get_hex_ascii(d1));
  uart_send_byte(get_hex_ascii(d0));
}

int main(void) {
  uart_init(9600, 0);
  sei();

  uint8_t t_i, t_f, h_i, h_f, cs, csc;

  while (1) {
    _delay_ms(2000);
    start_signal();
    response_signal();

    h_i = read_byte();
    h_f = read_byte();
    t_i = read_byte();
    t_f = read_byte();
    cs = read_byte();
    csc = h_i + h_f + t_i + t_f;

    if (csc - cs == 0) {
      uart_send_string("Humidity: ");
      uart_send_byte_as_dec(h_i);
      uart_send_byte(',');
      uart_send_byte_as_dec(h_f * 10);
      uart_send_string("% Temperature: ");
      uart_send_byte_as_dec(t_i);
      uart_send_byte(',');
      uart_send_byte_as_dec(t_f * 10);
      uart_send_string("°C");
    } else
      uart_send_string("Received invalid data");
    uart_send_string("\r\n");
  }

  return 0;
}
